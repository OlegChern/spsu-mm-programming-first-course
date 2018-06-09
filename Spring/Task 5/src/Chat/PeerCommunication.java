package Chat;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PeerCommunication {

    private List<Connection> peers;
    private MessageListener listener;

    PeerCommunication(MessageListener listenerObj) {
        peers = new ArrayList<>();
        listener = listenerObj;
    }

    public void addPeer(Socket peer) throws IOException {
        Connection temp = new Connection(peer, listener);
        peers.add(temp);
        listener.messageProcessing(new MessageEvent("A connection with " + temp.username + " has been established!", temp.getUsername(), MessageType.NewConnection));
    }

    public void sendToAll(String user, String message) {
        for (Connection currentPeer : peers) {
            if (!currentPeer.getUsername().equals(user)) {
                currentPeer.sendMessage(message);
            }
        }
    }

    public String getUserList() {
        StringBuilder result = new StringBuilder("");
        for (Connection currentPeer : peers) {
            result.append(currentPeer.getUsername());
            result.append("\n");
        }
        return result.toString();
    }

    public void greetUser(Socket connection, String username, String serverAddress, int serverPort) throws IOException {
        connection.getOutputStream().write((username + "\n").getBytes());
        connection.getOutputStream().write((serverAddress + "\n").getBytes());
        connection.getOutputStream().write((serverPort + "\n").getBytes());
    }

    public void establishNetwork(String network, String username, String serverAddress, int serverPort) {
        if (!network.equals("")) {
            String[] connections = network.split(" ");
            for (String currentConnection : connections) {
                Pattern pattern = Pattern.compile("((\\d?\\d?\\d\\.){3}(\\d?\\d?\\d\\:)(\\d?\\d?\\d?\\d?\\d))");
                Matcher matcher = pattern.matcher(currentConnection);
                try {
                    if (matcher.find()) {
                        String[] address = matcher.group().split(":");
                        Socket newConnection = new Socket(address[0], Integer.parseInt(address[1]));
                        greetUser(newConnection, username, serverAddress, serverPort);
                        addPeer(newConnection);
                    }
                } catch (IOException ex) {
                    System.err.println("Oops! Seems like one of the connections has not been severed properly!");
                }
            }
        }
    }

    private String getNetworkForPeer(Connection peer) {
        StringBuilder result = new StringBuilder("/network ");
        for (Connection currentPeer : peers) {
            if (currentPeer != peer) {
                result.append(currentPeer.getAddress());
                result.append(":");
                result.append(currentPeer.getPort());
                result.append(" ");
            }
        }
        return result.toString();
    }

    private boolean checkIfAlreadyConnected(String serverAddress, String serverPort) {
        for (Connection currentConnection: peers) {
            if (currentConnection.serverAddress.contains(serverAddress) &&
                    currentConnection.serverPort.equals(serverPort)) {
                return true;
            }
        }
        return false;
    }

    public void establishFirstConnection(String[] address, String username, String serverAddress, int serverPort) throws IOException, ConnectionException, InvalidInputFormatException {
        if (address.length < 2) {
            throw new InvalidInputFormatException("You have forgotten to enter the address you want to connect!");
        } else {
            String temp = address[1];
            Pattern pattern = Pattern.compile("((\\d?\\d?\\d\\.){3}(\\d?\\d?\\d\\:)(\\d?\\d?\\d?\\d?\\d))");
            Matcher matcher = pattern.matcher(temp);

            if (matcher.find()) {
                String connection[] = matcher.group().split(":");

                if (serverAddress.contains(connection[0]) && connection[1].equals(Integer.toString(serverPort))) {
                    throw new ConnectionException("It is forbidden to connect to yourself!");
                }

                if (checkIfAlreadyConnected(connection[0], connection[1])) {
                    throw new ConnectionException("Connection is already established!");
                }

                Socket peer = new Socket(connection[0], Integer.parseInt(connection[1]));
                greetUser(peer, username, serverAddress, serverPort);
                peer.getOutputStream().write(("/request\n").getBytes());
                addPeer(peer);
            }
            else {
                throw new InvalidInputFormatException("Invalid input format!");
            }
        }
    }

    class Connection extends Thread {

        String username;
        BufferedReader input;
        PrintWriter output;
        MessageListener listener;
        Socket peer;

        String serverAddress;
        String serverPort;

        Connection(Socket newPeer, MessageListener listenerObj) throws IOException {
            peer = newPeer;

            input = new BufferedReader(new InputStreamReader(peer.getInputStream()));
            output = new PrintWriter(peer.getOutputStream(), true);

            username = input.readLine();
            serverAddress = input.readLine();
            serverPort = input.readLine();

            listener = listenerObj;
            start();
        }

        String getAddress() {
            return serverAddress;
        }

        String getPort() {
            return serverPort;
        }

        void sendMessage(String message) {
            output.println(message);
        }

        String getUsername() {
            return username;
        }

        private boolean processMessage(String message) {
            if (message.equals("/exit")) {
                listener.messageProcessing(new MessageEvent(username + " has disconnected!", username, MessageType.Disconnect));
                peers.remove(this);
                return false;
            } else if (message.startsWith("/request")) {
                output.println(getNetworkForPeer(this));
            } else if (message.startsWith("/network")) {
                listener.messageProcessing(new MessageEvent(message, username, MessageType.ReceivedNetwork));
            } else {
                listener.messageProcessing(new MessageEvent(message, username, MessageType.ReceivedText));
            }
            return true;
        }

        @Override
        public void run() {
            String message;
            boolean isActive = true;
            try {
                while (isActive) {
                    message = input.readLine();
                    isActive = processMessage(message);
                }
            } catch (Exception ex) {
                System.err.println("Error occurred: " + ex.getMessage());
            }
        }
    }
}
