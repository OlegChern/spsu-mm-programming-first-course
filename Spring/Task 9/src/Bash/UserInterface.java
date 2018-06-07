package Bash;

import java.util.Scanner;

class UserInterface {

    private Scanner scanner;

    UserInterface() {
        scanner = new Scanner(System.in);
    }

    String getLine() {
        System.out.print(">>>");
        return scanner.nextLine();
    }

    void printResult(String result) {
        System.out.println(result);
    }

    void printError(Exception ex) {
        System.err.println(ex.getMessage());
    }
}
