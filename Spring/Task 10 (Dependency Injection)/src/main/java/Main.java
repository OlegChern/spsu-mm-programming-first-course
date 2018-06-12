import com.google.inject.Guice;
import com.google.inject.Injector;
import com.google.inject.Key;
import com.google.inject.name.Names;


public class Main {
    
    private static final Injector injector = Guice.createInjector(new IOCConfiguration());
    
    public static void main(String[] args) {
        
        GameController game = injector.getInstance(GameController.class);
    
        try {
            double startSum = injector.getInstance(Key.get(Integer.class, Names.named("START_SUM")));
            
//            game.registerPlayer(injector.getInstance(Human.class), "Alexander", startSum);
            game.registerPlayer(injector.getInstance(ShyBot.class), "Shy Boy", startSum);
            game.registerPlayer(injector.getInstance(StandardBot.class), "Usual Boy", startSum);
            game.registerPlayer(injector.getInstance(RiskyBot.class), "Risky Boy", startSum);
        } catch (RegistrationFailedException e) {
            System.out.println(e.getMessage());
        }
        
        game.play();
    }
}
