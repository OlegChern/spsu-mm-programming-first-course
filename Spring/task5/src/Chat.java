import java.io.IOException;
import java.net.Socket;
import java.util.Vector;

public class Chat {
    private ChatClient chatClient;
    private ChatServer server;
    private String username;
    private ClientInterface clientInterface;
    private NetworkController network;

    public Chat() {
        clientInterface = new ClientInterface();
        username = clientInterface.getUsername();
        network = new NetworkController(username, clientInterface);
        chatClient = new ChatClient(clientInterface);
        try {
            server = new ChatServer(network, clientInterface, chatClient);
            int serverPort = server.getPort();
            network.setServerPort(serverPort);
        } catch (IOException e) {
            clientInterface.errorMSG(e);
        }
        network.start();
        server.start();
    }

    public void run() {
        boolean flag = true;
        String tmp;
        while (flag) {
            tmp = clientInterface.readLine();
            if (tmp.length() > 0) {
                flag = runCommand(tmp);
            }
        }
        server.interrupt();
        network.interrupt();
        System.exit(0);
    }

    public boolean runCommand(String tmp) {
        boolean flag = true;
        if (tmp.charAt(0) == '/') {
            switch (tmp.charAt(1)) {
                case 'c':
                    if (tmp.split(" ").length == 3 && tmp.split(" ")[0].equals("/connect") && tmp.split(" ")[1].equals("to") && tmp.split(" ")[2].split(":").length == 2) {
                        connectTo(tmp.split(" ")[2].split(":")[0], Integer.parseInt(tmp.split(" ")[2].split(":")[1]));
                    }
                    break;
                case 'e':
                    if (tmp.equals("/exit")) {
                        flag = false;
                        disconnect();
                        clientInterface.printExitMSG();
                    }
                    break;
                case 'd':
                    if (tmp.equals("/disconnect")) {
                        disconnect();
                    }
                    break;
                case 'h':
                    if (tmp.equals("/help")) {
                        clientInterface.printHelp();
                    }
                    break;
                case 'u':
                    if (tmp.equals("/users")) {
                        printUsers();
                    }
                    break;
                default:
                    clientInterface.println("Wrong command");
            }
        } else {
            sendMSG(tmp);
        }
        return flag;
    }


    public void printUsers() {
        String tmp = network.getNetworkUsers();
        if (!tmp.equals("")) {
            clientInterface.println(tmp);
        } else {
            clientInterface.print("No users are connected!");
        }
    }

    public void sendMSG(String MSG) {
        network.sendToAll(MSG);
    }

    public void disconnect() {
        server.Pause();
        network.Pause();
        sendMSG("\0disconnect");
        network.disconnect();
        clientInterface.println("Disconnected from network! To become online connect to someone!");
    }

    public void connectTo(String IP, int port) {
        server.Continue();
        network.Continue();
        if (network.checkAddress(IP, port)) {
            clientInterface.println("Connection is still alive!!!");
            return;
        }
        Socket tmp = chatClient.connectTo(IP, port);
        ClientController extrauser;
        Vector<String> users;
        String[] address;
        ClientController clientController;
        try {
            network.Pause();
            clientController = network.add(tmp, true);
            //System.out.println(clientController.getUsername());
            if (clientController == null) {
                clientInterface.println("Connection failed!");
                network.Continue();
                return;
            }
            users = clientController.takeUsersList();
            //System.out.println(users.size());
            for (String client : users) {
                //System.out.println("'" + client + "'");
                if (client.equals("\0")) {
                    break;
                }
                address = client.split(":");
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
            clientInterface.println("Connection established!");
        } catch (IOException e) {
            clientInterface.errorMSG(e);
        }
    }
}