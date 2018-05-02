import Host.Host;
import Host.HostData;
import Host.UserData;

import java.io.IOException;
import java.net.BindException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.util.Scanner;


public class Main {
    
    private static int findAvailablePort() throws IOException {
        ServerSocket serverSocket = new ServerSocket(0);
        int port = serverSocket.getLocalPort();
        serverSocket.close();
        
        return port;
    }
    
    private static boolean testPort(int port) throws IOException {
        try {
            ServerSocket serverSocket = new ServerSocket(port);
            serverSocket.close();
        } catch (BindException be) {
            return false;
        }
        
        return true;
    }
    
    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(System.in);

            System.out.println("Input your name: ");
            String name = scanner.nextLine();

            System.out.println("Specify a local port (or input 0 to select it automatically): ");
            int port;
            while (true) {
                port = scanner.nextInt();
                if (port == 0) {
                    port = findAvailablePort();
                    System.out.println("Your local port is " + port);
                    break;
                }

                if (testPort(port)) {
                    break;
                } else {
                    System.out.println("Not enough rights to bind to the specified port or it is already engaged. Try again: ");
                }
            }

            Host we = new Host(new HostData(new InetSocketAddress(port)), new UserData(name));
            we.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
