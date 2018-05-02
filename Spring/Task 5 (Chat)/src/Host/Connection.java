package Host;

import java.io.*;
import java.net.Socket;
import java.net.SocketAddress;


/**
 * The envelope of the socket.
 * Input and output streams are kept here too for the sake of better performance
 * (opening and closing socket IO streams for the each operation is too expensive). IO streams
 * are enveloped in the {@linkplain ObjectInputStream} and {@linkplain ObjectOutputStream}
 * because all messages are transferred using the serialization mechanism.
 *
 * It also stores an information about the addressee from the other end of socket using
 * {@linkplain #addresseeHostData} and {@linkplain #addresseeUserData}.
 *
 * Connection is set via {@linkplain #connect(SocketAddress, int)} method.
 *
 * There are two main methods of sending and receiving messages:
 * @see #send(Object)
 * @see #receive()
 */
public class Connection {
    private Socket socket;
    private ObjectInputStream inputStream;
    private ObjectOutputStream outputStream;
    
    private HostData addresseeHostData;
    private UserData addresseeUserData;
    
    private static final int SOCKET_TIMEOUT = 200;
    
    /**
     * The main constructor of the connection. Connections should also have an info
     * about the other endpoint user ({@linkplain #addresseeHostData} and
     * {@linkplain #addresseeUserData}) but often there is not opportunity to
     * get it before the setting of the connection and getting this data from
     * the other endpoint according to the greeting protocol. That is why an
     * {@linkplain #addresseeHostData} and {@linkplain #addresseeUserData} are
     * explicitly set here as {@code null}.
     *
     * @param socket Socket on which this connections is based
     * @throws IOException From the sockets IO streams
     */
    Connection(Socket socket) throws IOException {
        this.socket = socket;
        this.socket.setSoTimeout(SOCKET_TIMEOUT);
        if (socket.isConnected()) {
            this.inputStream = new ObjectInputStream(socket.getInputStream());
            this.outputStream = new ObjectOutputStream(socket.getOutputStream());
        }
        this.addresseeHostData = null;
        this.addresseeUserData = null;
    }
    
    public Connection(Socket socket, HostData addresseeHostData, UserData addresseeUserData) throws IOException {
        this(socket);
        this.addresseeHostData = addresseeHostData;
        this.addresseeUserData = addresseeUserData;
    }
    
    void connect(SocketAddress socketAddress, int timeout) throws IOException {
        socket.connect(socketAddress, timeout);
        
        this.outputStream = new ObjectOutputStream(socket.getOutputStream());
        // other endpoint must firstly read an serialization header sent by this outputStream
        this.outputStream.flush();
        this.inputStream = new ObjectInputStream(socket.getInputStream());
    }
    
    public boolean isSet() {
        return socket.isConnected() && !socket.isClosed();
    }
    
    public boolean isReadable() {
        return isSet() && !socket.isInputShutdown();
    }
    
    public boolean isWritable() {
        return isSet() && !socket.isOutputShutdown();
    }
    
    public boolean isConnected() {
        return socket.isConnected();
    }
    
    public Object receive() throws IOException, ClassNotFoundException {
        return inputStream.readObject();
    }
    
    public void send(Object object) throws IOException {
        outputStream.writeObject(object);
        outputStream.flush();
    }
    
    public HostData getAddresseeHostData() {
        return addresseeHostData;
    }
    
    public void setAddresseeHostData(HostData addresseeHostData) {
        this.addresseeHostData = addresseeHostData;
    }
    
    public UserData getAddresseeUserData() {
        return addresseeUserData;
    }
    
    public void setAddresseeUserData(UserData addresseeUserData) {
        this.addresseeUserData = addresseeUserData;
    }
    
    public void close() throws IOException {
        outputStream.close();
        inputStream.close();
        socket.close();
    }
    
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Connection)) {
            return false;
        }
        
        Connection other = (Connection) obj;
        return socket.getRemoteSocketAddress().equals(other.socket.getRemoteSocketAddress());
    }
}
