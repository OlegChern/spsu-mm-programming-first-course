import com.google.inject.AbstractModule;
import com.google.inject.Provides;
import com.google.inject.name.Named;
import com.google.inject.name.Names;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;


public class IOCConfiguration extends AbstractModule {
    @Override
    protected void configure() {
        // setting commentator instance
        bind(Commentator.class).toInstance(new Commentator(new PrintWriter(System.out, true)));
        
        // setting game parameters
        bind(Integer.class).annotatedWith(Names.named("DURATION")).toInstance(40);
        bind(Integer.class).annotatedWith(Names.named("DECKS_COUNT")).toInstance(8);
        bind(Integer.class).annotatedWith(Names.named("MINIMUM_BET")).toInstance(5);
        bind(Integer.class).annotatedWith(Names.named("START_SUM")).toInstance(1000);
        
        // setting humans I/O streams
        bind(InputStream.class).annotatedWith(Names.named("HUMAN_INPUT_STREAM")).toInstance(System.in);
        bind(OutputStream.class).annotatedWith(Names.named("HUMAN_OUTPUT_STREAM")).toInstance(System.out);
    }
    
    // creates and tunes game controller instance
    @Provides
    GameController provideGameController(@Named("DURATION") Integer duration,
                                         @Named("DECKS_COUNT") Integer decksCount,
                                         @Named("MINIMUM_BET") Integer minimumBet,
                                         Commentator commentator) {
        GameController gameController = new GameController();
        
        gameController.setDuration(duration);
        gameController.setDecksCount(decksCount);
        gameController.setMinimumBet(minimumBet);
        gameController.setCommentator(commentator);
        
        return gameController;
    }
}
