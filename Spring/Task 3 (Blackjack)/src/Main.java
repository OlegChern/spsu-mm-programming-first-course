import java.io.PrintWriter;

public class Main {
    
    private static final int DURATION = 40;
    private static final int DECKS_COUNT = 8;
    private static final int START_SUM = 1000;
    private static final int MINIMUM_BET = 5;
    
    private static final Commentator COMMENTATOR = new Commentator(new PrintWriter(System.out, true));
    
    public static void main(String[] args) {
        
        GameController game = new GameController();
    
        try {
//            game.registerPlayer(new Human(System.in, System.out), "Alexander", START_SUM);
            game.registerPlayer(new ShyBot(), "Shy Boy", START_SUM);
            game.registerPlayer(new StandardBot(), "Usual Boy", START_SUM);
            game.registerPlayer(new RiskyBot(), "Risky Boy", START_SUM);
        } catch (RegistrationFailedException e) {
            System.out.println(e.getMessage());
        }
    
        //region settings
        game.setDuration(DURATION);
        game.setDecksCount(DECKS_COUNT);
        game.setMinimumBet(MINIMUM_BET);
        game.setCommentator(COMMENTATOR);
        //endregion
        
        game.play();
    }
}
