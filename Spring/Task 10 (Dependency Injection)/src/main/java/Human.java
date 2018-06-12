import com.google.inject.Inject;
import com.google.inject.name.Named;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Scanner;

public class Human implements Player {
    
    private Scanner scanner;
    private PrintWriter printWriter;
    
    @Inject
    public Human(@Named("HUMAN_INPUT_STREAM") InputStream inputStream, @Named("HUMAN_OUTPUT_STREAM") OutputStream outputStream) {
        scanner = new Scanner(inputStream);
        printWriter = new PrintWriter(outputStream, true);
    }
    
    @Override
    public double makeBet(double playerMoney, double minimumBet) {
        printWriter.println("You have " + playerMoney + ", minimum one is " + minimumBet + ". Input your bet: ");
        while (true) {
            try {
                return Double.parseDouble(scanner.next());
            } catch (NumberFormatException e) {
                printWriter.println("Incorrect input, try again: ");
            }
        }
    }
    
    @Override
    public Action act(Hand hand, GameState gameState) {
        printWriter.println("Your hand: " + hand);
        printWriter.println("Dealer's card: " + gameState.getDealerOpenCard());
        
        while (true) {
            printWriter.println("Input action [hit|stand|double|split]: ");
            String input = scanner.next().toLowerCase();
            
            switch (input) {
                case "hit":
                    return Action.HIT;
                case "stand":
                    return Action.STAND;
                case "double":
                    return Action.DOUBLE;
                case "split":
                    return Action.SPLIT;
                default:
                    printWriter.println("Incorrect input, try again");
            }
        }
    }
}
