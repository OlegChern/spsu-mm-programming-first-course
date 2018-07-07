import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

public class ChatServer extends Thread {
    private ServerSocket server;
    private int port;
    private ChatClient chatClient;
    private NetworkController network;
    private ClientInterface clientInterface;
    public ChatServer(NetworkController network, ClientInterface clientInterface, ChatClient chatClient) throws IOException {
        server = new ServerSocket(0);
        this.chatClient = chatClient;
        this.network = network;
        this.clientInterface = clientInterface;
        String IP = server.getInetAddress().toString();
        port = server.getLocalPort();
        clientInterface.println("You are now available for connections\nYour IP and port: " + IP.split("/")[0] + ":" + port);
    }

    public int getPort() {
        return port;
    }

    @Override
    public void run() {
        ClientController clientController, extrauser;
        Vector<String> users;
        String[] address;

        try {
            while (true) {
                Socket client = server.accept();
                network.Pause();
                clientController = network.add(client);
                if (clientController == null) {
                    continue;
                }
                users = clientController.takeUsersList();
                for (String user : users) {
                    if (user.equals("\0")) {
                        break;
                    }
                    address = user.split(":");
                    if (network.checkAddress(address[0], Integer.parseInt(address[1]))) {
                        continue;
                    }
                    extrauser = network.add(chatClient.connectTo(address[0], Integer.parseInt(address[1])));
                    if (extrauser == null) {
                        continue;
                    }
                    extrauser.takeUsersList();
                }
                network.Continue();
                if (isInterrupted()) {
                    break;
                }
            }
        } catch (IOException e) {
            clientInterface.errorMSG(e);
        }
    }
}