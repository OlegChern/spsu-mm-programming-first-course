import java.util.Scanner;

public class ClientInterface {

    private Scanner sc;

    public ClientInterface() {
        sc = new Scanner(System.in);
        printWelcomeMSG();
    }

    public void printWelcomeMSG() {
        System.out.println("Welcome to CHAT v 1.0!!!");
    }

    public String getUsername() {
        System.out.println("Please enter your username:");
        return sc.nextLine();
    }

    public void println(String MSG) {
        System.out.println(MSG);
    }

    public void print(String MSG) {
        System.out.print(MSG);
    }

    public void errorMSG(Exception e) {
        e.printStackTrace();
    }

    public String readLine() {
        return sc.nextLine();
    }

    public void printHelp() {
        System.out.println("Available commands:\n1) /connect to IP:Port\n2) /exit\n3) /disconnect\n4) /help\n5) /users\nIf you are connected to network just enter smth to send it to the network!");
    }

    public void printExitMSG() {
        System.out.println("Goodbye");
    }


}