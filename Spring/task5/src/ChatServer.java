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
    private boolean pauseFlag;
    public ChatServer(NetworkController network, ClientInterface clientInterface, ChatClient chatClient) throws IOException {
        server = new ServerSocket(0);
        this.chatClient = chatClient;
        this.network = network;
        this.clientInterface = clientInterface;
        String IP = server.getInetAddress().toString();
        port = server.getLocalPort();
        pauseFlag = false;
        clientInterface.println("You are now available for connections\nYour IP and port: " + IP.split("/")[0] + ":" + port);
    }

    public void Pause() {
        this.pauseFlag = true;
    }

    public void Continue() {
        this.pauseFlag = false;
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
                if (pauseFlag) {
                    while (pauseFlag) {
                        try {
                            wait(10);
                        } catch (InterruptedException e) {
                            return;
                        }
                    }
                    continue;
                }
                network.Pause();
                clientController = network.add(client, false);
                //System.out.println(clientController.getUsername());
                if (clientController == null) {
                    network.Continue();
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
                    extrauser = network.add(chatClient.connectTo(address[0], Integer.parseInt(address[1])), false);
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
