package Chat;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Peer implements MessageListener {

    private String username;
    private String userAddress;
    private int userPort;

    private UserInterface UI;
    private PeerCommunication network;

    public Peer() throws IOException {
        UI = new UserInterface(this);
        this.username = UI.getUsername();
        UI.start();

        network = new PeerCommunication(this);
        new Server().start();
    }

    @Override
    public void messageProcessing(MessageEvent event) {
        try {
            switch (event.getType()) {
                case Exit: {
                    network.sendToAll(this.username, event.getText());
                    System.exit(0);
                }
                case InvalidCommand: {
                    UI.printError(new Exception("Invalid command"));
                    break;
                }
                case SentText: {
                    network.sendToAll(this.username, event.getText());
                    break;
                }
                case ReceivedText: {
                    String message = event.getUser() + " says: " + event.getText();
                    UI.printMessage(message);
                    break;
                }
                case Connect: {
                    network.establishFirstConnection(event.getText().split(" "), username, userAddress, userPort);
                    break;
                }
                case NewConnection: {
                    UI.printMessage(event.getText());
                    break;
                }
                case ReceivedNetwork: {
                    String rawNetwork = event.getText().replaceFirst("/network ", "");
                    network.establishNetwork(rawNetwork, username, userAddress, userPort);
                    break;
                }
                case Disconnect: {
                    UI.printMessage(event.getText());
                    break;
                }
                case Help: {
                    UI.printHelp();
                    break;
                }
                case List: {
                    String list = network.getUserList();
                    list = list.concat(username);
                    UI.printUserList(list);
                }
            }
        } catch (Exception ex) {
            UI.printError(ex);
        }
    }

    class Server extends Thread {

        ServerSocket server;

        Server() throws IOException {
            server = new ServerSocket(0);
            userAddress = server.getInetAddress().toString();
            userPort = server.getLocalPort();
        }

        @Override
        public void run() {
            System.out.println("The chat is running now! Your address is: " + userAddress + ":" + userPort);
            System.out.println("To get instructions type /help");
            try {
                while (true) {
                    Socket peer = server.accept();
                    network.greetUser(peer, username, userAddress, userPort);
                    network.addPeer(peer);
                }
            } catch (IOException ex) {
                UI.printError(ex);
            }
        }
    }
}
