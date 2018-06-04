package Chat;

import java.util.Scanner;

public class UserInterface extends Thread {

    private Scanner scanner;
    private MessageListener listener;

    private static final String helpText = "\n" +
            "Available commands:\n" +
            "/connect AAA.BBB.CCC.DDD:PPPPP - establish a connection with desired address\n" +
            "/exit - disconnect from current chat and exit the program\n" +
            "/list - print the list of users currently in chat\n" +
            "/help - get help message\n";

    UserInterface(MessageListener listener) {
        this.listener = listener;
        this.scanner = new Scanner(System.in);
    }

    public void printUserList(String list) {
        System.out.println("Users currently in chat:");
        System.out.println(list);
    }

    public void printHelp() {
        System.out.println(helpText);
    }

    public void printError(Exception ex) {
        System.err.println("Error occurred: " + ex.getMessage());
    }

    public void printMessage(String message) {
        System.out.println(message);
    }

    public String getUsername() {
        System.out.print("Please enter your username: ");
        return scanner.nextLine();
    }

    private void sendMessage(String message) {
        listener.messageProcessing(new MessageEvent(message));
    }

    @Override
    public void run() {
        String getMessage;
        while (true) {
            getMessage = scanner.nextLine();
            if (!getMessage.startsWith("/"))
                System.out.println("You say: " + getMessage);

            sendMessage(getMessage);
        }
    }

}
