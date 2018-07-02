import java.net.*;

public class ChatClient {

    private ClientInterface clientInterface;

    public ChatClient(ClientInterface clientInterface) {
        this.clientInterface = clientInterface;
    }

    public Socket connectTo(String IP, int port) {
        try {
            InetAddress ipAddress = InetAddress.getByName(IP);
            return new Socket(ipAddress, port);
        } catch (Exception e) {
            clientInterface.println("This address is unavailable for connecting!");
            return null;
        }
    }


}
