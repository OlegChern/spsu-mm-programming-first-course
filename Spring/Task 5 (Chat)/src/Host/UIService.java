package Host;

import java.io.*;
import java.net.ConnectException;
import java.net.InetSocketAddress;
import java.net.SocketTimeoutException;
import java.util.concurrent.atomic.AtomicBoolean;


/**
 * User interface service is responsible for:
 * 1.) reception commands from user and transmission them to the according services
 * 2.) printing messages for user from program and other users
 *
 * It also provides some envelopes for other services functions with feedback of their
 * processing and (or) result to the user.
 * @see #connectWithUIFeedbackTo(InetSocketAddress)
 *
 * Service works in its own thread.
 *
 * It also provides {@linkplain #onTermination} function which is called when user
 * prints command of exit {@linkplain #QUIT_COMMAND_REGEX}. It allows set some actions
 * (for example stopping other services) on the finishing UI service.
 */
public class UIService implements Runnable {
    private Thread worker;
    private final AtomicBoolean isRunning = new AtomicBoolean(false);
    
    private BufferedReader userInput;
    private PrintWriter userOutput;
    
    private ConnectionsService connectionsService;
    private MessagesService messagesService;
    
    private OnTermination onTermination;
    
    /**
     * List of regexps of all possible user commands.
     */
    private static final String CONNECT_COMMAND_REGEX = "^/connectTo .*";
    private static final String LIST_ALL_COMMAND_REGEX = "^/listAll$";
    private static final String QUIT_COMMAND_REGEX = "^/quit$";
    
    /**
     * Regexps for the parsing socket address from connections command.
     * @see #CONNECT_COMMAND_REGEX
     */
    private static final String IP_REGEX = "(([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.){3}([01]?\\d\\d?|2[0-4]\\d|25[0-5])";
    private static final String PORT_REGEX = "([0-5]\\d{0,5}|6[0-4]\\d{0,4}|65[0-4]\\d{0,3}|655[0-2]\\d{0,2}|6553[0-5])";
    private static final String SOCKET_ADDRESS_REGEX = IP_REGEX + ":" + PORT_REGEX;
    
    /**
     * The only constructor of UI service. UI service is based on the {@linkplain ConnectionsService}
     * and is unable to work without it, that is why it is a mandatory first param.
     *
     * @param connectionsService connections services on which this UI services will be based
     * @param userInput input stream from which this service reads user commands
     * @param userOutput output stream where this service prints feedback for the user
     */
    UIService(ConnectionsService connectionsService, InputStream userInput, OutputStream userOutput) {
        this.connectionsService = connectionsService;
        this.userInput = new BufferedReader(new InputStreamReader(userInput));
        this.userOutput = new PrintWriter(userOutput, true);
    }
    
    public void start() {
        worker = new Thread(this);
        isRunning.set(true);
        worker.start();
    }
    
    public void stop() {
        isRunning.set(false);
    }
    
    @Override
    public void run() {
        while (isRunning.get()) {
            try {
                String command = userInput.readLine().trim();
                
                if (command.length() == 0) {
                    continue;
                }
                
                if (command.charAt(0) == '/') {
                    if (command.matches(CONNECT_COMMAND_REGEX)) {
                        String argument = command.split(" ", 2)[1].trim();
                        
                        if (!argument.matches(SOCKET_ADDRESS_REGEX)) {
                            printMessageFromProgram("Incorrect format of socket address. Follow an example format: 127.0.0.1:4444");
                            continue;
                        }
                        connectWithUIFeedbackTo(inetSocketAddressFromString(argument));
                        
                    } else if (command.matches(LIST_ALL_COMMAND_REGEX)) {
                        if (connectionsService.hasConnections()) {
                            connectionsService.getConnections().forEach((c) -> {
                                userOutput.println(c.getAddresseeUserData().getName() +
                                        " via " + c.getAddresseeHostData().getServerSocketAddress());
                            });
                        } else {
                            printMessageFromProgram("No users in chat but you :c");
                        }
                    } else if (command.matches(QUIT_COMMAND_REGEX)) {
                        onTermination.perform();
                        stop();
                    } else {
                        printMessageFromProgram("Unknown command: " + command);
                    }
                    
                } else {
                    if (!connectionsService.hasConnections()) {
                        printMessageFromProgram("TextMessage did not delivered: no users in chat but you");
                    } else {
                        if (messagesService != null) {
                            messagesService.sendMessageToAll(new TextMessage(command));
                        }
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    
        try {
            close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    static InetSocketAddress inetSocketAddressFromString(String representation) {
        String[] parts = representation.split(":");
        return new InetSocketAddress(parts[0], Integer.parseInt(parts[1]));
    }
    
    public void connectWithUIFeedbackTo(InetSocketAddress newHostAddress) {
        try {
            if (connectionsService.isConnectedWith(newHostAddress)) {
                printMessageFromProgram("You are already connected with " + newHostAddress);
            } else {
                if (connectionsService.connectTo(newHostAddress)) {
                    printMessageFromProgram("Connection with " + newHostAddress + " is set");
                } else {
                    printMessageFromProgram("Greeting protocol with " + newHostAddress + " failed");
                }
            }
        } catch (SocketTimeoutException ste) {
            printMessageFromProgram("Connection timeout exceeded");
        } catch (ConnectException ce) {
            printMessageFromProgram("It is impossible to set the connection: " + ce.getMessage());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public void printMessageFromProgram(String message) {
        userOutput.println("*** " + message + " ***");
    }
    
    public void printMessageFromConferees(String confereeName, String message) {
        userOutput.println("From " + confereeName + ": " + message);
    }
    
    public void close() throws IOException {
        userInput.close();
        userOutput.close();
    }
    
    public void setMessagesService(MessagesService messagesService) {
        this.messagesService = messagesService;
    }
    
    public void setOnTermination(OnTermination onTermination) {
        this.onTermination = onTermination;
    }
}
