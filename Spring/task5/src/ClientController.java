import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Vector;

public class ClientController {

    private BufferedReader input;
    private PrintWriter output;
    private String username;
    private int serverPort;
    private String IP;

    public ClientController(Socket client, String username, int serverPort) throws IOException {
        input = new BufferedReader(new InputStreamReader(client.getInputStream()));
        output = new PrintWriter(client.getOutputStream(), true);
        send(username);
        this.username = input.readLine();
        send(Integer.toString(serverPort));
        this.serverPort = Integer.parseInt(input.readLine());
        IP = client.getInetAddress().toString();
    }

    public BufferedReader getInput() {
        return input;
    }

    public Vector<String> takeUsersList() throws IOException {
        String tmp;
        Vector<String> list = new Vector<>();
        while (!((tmp = input.readLine()).equals("\0"))) {
            list.add(tmp);
        }
        return list;
    }

    public int getPort() {
        return serverPort;
    }

    public String getIP() {
        return IP;
    }

    public void send(String MSG) {
        output.println(MSG);
    }

    public String getUsername() {
        return username;
    }
}