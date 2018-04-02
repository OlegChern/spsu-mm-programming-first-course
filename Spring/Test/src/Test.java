import java.util.Scanner;

public class Test {

    public static void main(String[] argv) {

        System.out.print("Please, enter a line: ");

        Scanner input = new Scanner(System.in);

        if (input.hasNextInt()) {

            Message newMess = new MessageInt(input.nextInt());

            newMess.format();
            newMess.printMess();

        } else {

            Message newMess = new MessageString(input.nextLine());

            newMess.format();
            newMess.printMess();
        }

    }
}
