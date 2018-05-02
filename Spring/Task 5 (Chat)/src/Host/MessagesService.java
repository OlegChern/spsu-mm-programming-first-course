package Host;

import java.io.IOException;
import java.net.SocketTimeoutException;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.ScheduledFuture;
import java.util.concurrent.TimeUnit;


/**
 * Messages service is responsible for:
 * 1.) sending messages for the all connections from the {@linkplain #connectionsService}
 *      connections list (via {@linkplain ConnectionsService#getConnections()} method).
 *      @see #sendMessageToAll(Message)
 * 2.) observing messages from the all connections from the {@linkplain #connectionsService}
 *      connections list (via {@linkplain ConnectionsService#getConnections()} method).
 *
 * Service works in its own thread. It observes by timer each {@linkplain #PERIOD} {@linkplain #TIME_UNIT}.
 * @see #scheduledExecutorService
 * @see #INITIAL_DELAY
 * @see #PERIOD
 * @see #TIME_UNIT
 *
 * All mesages are received and sent using serialization via {@linkplain Connection#inputStream} and
 * {@linkplain Connection#outputStream}. All messages are packed to the according envelope of message:
 * @see Message
 * @see TextMessage
 * @see SystemMessage
 */
public class MessagesService implements Runnable {
    private ScheduledExecutorService scheduledExecutorService;
    private ScheduledFuture<?> handler;
    
    private static final int INITIAL_DELAY = 1;
    private static final int PERIOD = 1;
    private static final TimeUnit TIME_UNIT = TimeUnit.SECONDS;
    
    private ConnectionsService connectionsService;
    private UIService uiService;
    
    /**
     * The only constructor of the messages service. Each messages service is based
     * on the {@linkplain #connectionsService}, on which connections it observes new
     * messages and where it sends user messages, and on the {@linkplain #uiService},
     * where it prints received messages.
     *
     * @param connectionsService connection service which connection are for the observing
     * @param uiService UI service where received messages are transfer to
     */
    public MessagesService(ConnectionsService connectionsService, UIService uiService) {
        this.connectionsService = connectionsService;
        this.uiService = uiService;
    }
    
    public void start() {
        scheduledExecutorService = Executors.newSingleThreadScheduledExecutor();
        handler = scheduledExecutorService.scheduleAtFixedRate(this, INITIAL_DELAY, PERIOD, TIME_UNIT);
    }
    
    public void stop() {
        handler.cancel(true);
        scheduledExecutorService.shutdownNow();
    }
    
    @Override
    public void run() {
        for (Connection connection : connectionsService.getConnections()) {
            try {
                while (connection.isReadable()) {
                    Object data = connection.receive();
                    
                    if (data instanceof TextMessage) {
                        uiService.printMessageFromConferees(
                                connection.getAddresseeUserData().getName(), ((TextMessage) data).getText());
                    } else if (data instanceof SystemMessage) {
                        if (((SystemMessage) data).getCommandID() == SystemMessageCommandsList.KILL_CONNECTION_MARK) {
                            if (connectionsService.disconnectFrom(connection)) {
                                uiService.printMessageFromProgram(
                                        connection.getAddresseeUserData().getName() + " left the chat");
                            }
                        }
                    } else {
                        throw new InappropriateMessageTypeException();
                    }
                }
            } catch (SocketTimeoutException ignored) {
                // unfortunately there is no any solution to add timeout on reading
                // except force it by socket timeout. So that timeout is ok
            } catch (IOException e) {
                // in the case if addressee terminates accidentally
                try {
                    connectionsService.disconnectFrom(connection);
                    uiService.printMessageFromProgram(
                            connection.getAddresseeUserData().getName() + " left the chat");
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }
    
    public void sendMessageToAll(Message message) {
        connectionsService.getConnections().forEach(connection -> {
            if (connection.isWritable()) {
                try {
                    connection.send(message);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
