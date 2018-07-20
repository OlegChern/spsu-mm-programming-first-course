package Bash;

import java.util.Scanner;

public class ClientInterface {

    private Scanner sc;

    public ClientInterface() {
        sc = new Scanner(System.in);
    }

    public String getCommand() {
        return sc.nextLine();
    }

    public void println(String MSG) {
        if (!MSG.equals("")) {
            System.out.println(MSG);
        }
    }

    public void printExitMSG() {
        System.out.println("Goodbye");
    }

    public void printWelcomeMSG() {
        System.out.println("Welcome to OLesya BASH v 1.0");
    }

    public void print(char i) {
        System.out.print(i);
    }

    public void print(String i) {
        System.out.print(i);
    }
}

