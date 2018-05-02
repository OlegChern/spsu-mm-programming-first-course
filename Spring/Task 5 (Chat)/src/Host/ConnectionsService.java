package Host;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;


/**
 * Connections service is responsible for:
 * 1.) setting own connections by request
 * 2.) receptions incoming connections
 * 3.) breaking connections
 *
 * Works in its own thread.
 *
 * Service also provides setting a greeting protocol which consists of:
 * 1.) {@linkplain #performGreeting} function. When service sets
 *      new connection it calls this function with new connection to let it perform greeting.
 *      If function returns true, what means that greeting protocol was performed
 *      successfully, connections service adds new connection to its list. By the way,
 *      there is an opportunity for the {@code PerformGreeting} function to add new
 *      connection manually (via {@code getConnections()}) if it is needed.
 * 2.) {@linkplain #acceptGreeting} function. When service receives
 *      incoming connection it calls this function to accept greeting (second part of greeting protocol).
 *      If function returns true, what means that greeting protocol was performed
 *      successfully, connections service adds new connection to its list. There is
 *      also an opportunity for {@code AcceptGreeting} function to add new connection
 *      to the list manually if it is needed.
 *
 * Service provides {@linkplain #onConnectionServiceClosure} function which is run for each
 * connection in connections list when service is stopping after call of {@linkplain #stop()}.
 */
public class ConnectionsService implements Runnable {
    private Thread worker;
    private final AtomicBoolean isRunning = new AtomicBoolean(false);
    
    private ServerSocket connectionsListener;
    private ConcurrentLinkedDeque<Connection> connections;
    
    private PerformGreeting performGreeting;
    private AcceptGreeting acceptGreeting;
    
    private OnConnectionServiceClosure onConnectionServiceClosure;
    
    private static final int CONNECTION_TIMEOUT = 3000;
    
    ConnectionsService(int localPort) throws IOException {
        this.connectionsListener = new ServerSocket(localPort);
        this.connections = new ConcurrentLinkedDeque<>();
    }
    
    public void start() {
        worker = new Thread(this);
        isRunning.set(true);
        worker.start();
    }
    
    public void stop() {
        isRunning.set(false);
        try {
            connectionsListener.close();
        } catch (IOException ignored) {
        
        }
    }
    
    @Override
    public void run() {
        try {
            while (isRunning.get()) {
                try {
                    Connection newSubscriber = new Connection(connectionsListener.accept());
                    
                    if (acceptGreeting == null || acceptGreeting.answer(newSubscriber)) {
                        // greeting protocol might have already add connection so we should check it
                        if (!isConnectedWith(newSubscriber)) {
                            connections.add(newSubscriber);
                        }
                    }
                } catch (SocketException se) {
                    // when we force connectionListener to stop listening it produces SocketException
                    // it is treated as supposed and that is why it is ignored here
                }
            }
            
            for (Connection connection : connections) {
                if (onConnectionServiceClosure != null) {
                    onConnectionServiceClosure.performLastAction(connection);
                }
                disconnectFrom(connection);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private Connection getConnectionByAddress(InetSocketAddress serverSocketAddress) {
        return connections.stream()
                .filter(c -> c.getAddresseeHostData().getServerSocketAddress().equals(serverSocketAddress))
                .findFirst()
                .orElse(null);
    }
    
    public boolean isConnectedWith(InetSocketAddress serverSocketAddress) {
        return getConnectionByAddress(serverSocketAddress) != null;
    }
    
    public boolean isConnectedWith(Connection connection) {
        return connections.contains(connection);
    }
    
    public boolean connectTo(InetSocketAddress serverSocketAddress) throws IOException {
        if (isConnectedWith(serverSocketAddress)) {
            return true;
        }
        
        Connection connection = new Connection(new Socket());
        connection.connect(serverSocketAddress, CONNECTION_TIMEOUT);
        
        if (performGreeting == null || performGreeting.greet(connection)) {
            // greeting protocol might have already add connection so we should check it
            if (!isConnectedWith(connection)) {
                connections.add(connection);
            }
            return true;
        }
        
        return false;
    }
    
    public boolean disconnectFrom(InetSocketAddress serverSocketAddress) throws IOException {
        for (Iterator<Connection> iterator = connections.iterator(); iterator.hasNext(); ) {
            Connection connection = iterator.next();
            
            if (connection.getAddresseeHostData().getServerSocketAddress().equals(serverSocketAddress)) {
                connection.close();
                iterator.remove();
                return true;
            }
        }
        
        return false;
    }
    
    public boolean disconnectFrom(Connection breakingConnection) throws IOException {
        for (Iterator<Connection> iterator = connections.iterator(); iterator.hasNext(); ) {
            Connection connection = iterator.next();
        
            if (connection.equals(breakingConnection)) {
                connection.close();
                iterator.remove();
                return true;
            }
        }
    
        return false;
    }
    
    ConcurrentLinkedDeque<Connection> getConnections() {
        return connections;
    }
    
    public boolean hasConnections() {
        return !connections.isEmpty();
    }
    
    public void setPerformGreeting(PerformGreeting performGreeting) {
        this.performGreeting = performGreeting;
    }
    
    public void setAcceptGreeting(AcceptGreeting acceptGreeting) {
        this.acceptGreeting = acceptGreeting;
    }
    
    public void setOnConnectionServiceClosure(OnConnectionServiceClosure onConnectionServiceClosure) {
        this.onConnectionServiceClosure = onConnectionServiceClosure;
    }
}


