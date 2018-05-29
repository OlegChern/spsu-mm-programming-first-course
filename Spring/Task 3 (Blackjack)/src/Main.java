public class Main {
    
    private static final int START_SUM = 1000;
    
    private static final int DURATION = 40;
    
    public static void main(String[] args) {
        
        GameController game = new GameController();
    
        try {
//            game.registerPlayer(new Human(), "Alexander", START_SUM);
            game.registerPlayer(new ShyBot(), "Shy Boy", START_SUM);
            game.registerPlayer(new StandardBot(), "Usual Boy", START_SUM);
            game.registerPlayer(new RiskyBot(), "Risky Boy", START_SUM);
        } catch (RegistrationFailedException e) {
            System.out.println(e.getMessage());
        }
    
        game.setDuration(DURATION);
        
        game.play();
    }
}
