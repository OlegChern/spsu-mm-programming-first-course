import java.util.Scanner;

public class Human implements Player {
    
    private Scanner scanner = new Scanner(System.in);
    
    @Override
    public double makeBet(double playerMoney, double minimumBet) {
        System.out.println("You have " + playerMoney + ", minimum one is " + minimumBet + ". Input your bet: ");
        while (true) {
            try {
                return Double.parseDouble(scanner.next());
            } catch (NumberFormatException e) {
                System.out.println("Incorrect input, try again: ");
            }
        }
    }
    
    @Override
    public Action act(Hand hand, GameState gameState) {
        System.out.println("Your hand: " + hand);
        System.out.println("Dealer's card: " + gameState.getDealerOpenCard());
        
        while (true) {
            System.out.println("Input action [hit|stand|double|split]: ");
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
                    System.out.println("Incorrect input, try again");
            }
        }
    }
}
