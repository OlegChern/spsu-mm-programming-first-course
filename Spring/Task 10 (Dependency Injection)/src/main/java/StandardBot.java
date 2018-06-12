import com.google.inject.Inject;

import java.util.Random;

public class StandardBot implements Player {
    Random random = new Random();
    
    @Inject
    public StandardBot() {
    }
    
    @Override
    public double makeBet(double playerMoney, double minimumBet) {
        return minimumBet * (random.nextInt(5) + 1);
    }
    
    @Override
    public Action act(Hand hand, GameState gameState) {
        if (hand.isSplittable()) {
            return Action.SPLIT;
        }
        
        if (hand.getScore() < 12) {
            return Action.DOUBLE;
        }
        
        if (hand.getScore() < 15) {
            return Action.HIT;
        }
        
        return Action.STAND;
    }
}
