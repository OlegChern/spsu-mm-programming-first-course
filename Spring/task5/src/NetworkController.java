import java.io.IOException;
import java.net.Socket;
import java.util.Vector;

public class NetworkController extends Thread {
    private Vector <ClientController> clients;
    private String username;
    private boolean pauseFlag;
    private int serverPort;
    private ClientInterface clientInterface;

    public NetworkController(String username, ClientInterface clientInterface) {
        clients = new Vector<>();
        this.username = username;
        this.clientInterface = clientInterface;
        pauseFlag = false;
    }

    public void setServerPort(int serverPort) {
        this.serverPort = serverPort;
    }

    public String getNetworkUsers() {
        String list = "";
        for (ClientController clientController : clients) {
            list += clientController.getUsername() + "\n";
        }
        return list;
    }

    public void sendToAll(String MSG) {
        for (ClientController clientController : clients) {
            clientController.send(MSG);
        }
    }

    public ClientController add(Socket client, boolean flag) {
        try {
            ClientController clientController = new ClientController(client, username, serverPort);
            sendContactList(clientController);
            if (!check(clientController.getUsername())) {
                clients.add(clientController);
                clientInterface.println("SYSTEM: New user with username '" + clientController.getUsername() + "' connected!");
                return clientController;
            } else if (flag) {
                clientInterface.println("This user is in your userlist!!!");
                return null;

            }
        } catch (IOException e) {
            clientInterface.errorMSG(e);
        }
        return null;
    }

    public void sendContactList(ClientController clientController) {
        for (ClientController client : clients) {
            //System.out.println(client.getIP().split("/")[0] + ":" + client.getPort());
            clientController.send(client.getIP().split("/")[1] + ":" + client.getPort());
        }
        clientController.send("\0");
    }

    public void disconnect() {
        clients = new Vector<>();
    }

    public void Continue() {
        pauseFlag = false;
        //System.out.println("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
    }

    public void Pause() {
        pauseFlag = true;
        //System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }

    public boolean check(String username) {
        for (ClientController client : clients) {
            if (client.getUsername().equals(username)) {
                return true;
            }
        }
        return false;
    }

    public boolean checkAddress(String IP, int port) {
        for (ClientController client : clients) {
            if ((client.getPort() == port) && (client.getIP().split("/")[1].equals(IP))) {
                return true;
            }
        }
        return false;
    }

    @Override
    public synchronized void run() {
        String MSG;
        while (true) {
            while (pauseFlag) {
                try {
                    wait(10);
                } catch (InterruptedException e) {
                    return;
                }
            }
            if (clients.size() > 0) {
                for (ClientController client : clients) {
                    try {
                        if (client.getInput().ready()) {
                            MSG = client.getInput().readLine();
                        } else {
                            continue;
                        }
                        if (MSG.equals("\0disconnect")) {
                            clientInterface.println(client.getUsername() + " disconnected!");
                            clients.remove(client);
                            break;
                        }
                        if (isInterrupted()) {
                            return;
                        }
                        if (MSG.charAt(0) == '\0') {
                            MSG = MSG.substring(1);
                        } else {
                            MSG = client.getUsername() + ": " + MSG;
                        }
                        clientInterface.println(MSG);
                    } catch (IOException e) {
                        clientInterface.println(client.getUsername() + " disconnected!");
                        clients.remove(client);
                        break;
                    }
                    if (isInterrupted()) {
                        return;
                    }
                }
            }
        }
    }


}