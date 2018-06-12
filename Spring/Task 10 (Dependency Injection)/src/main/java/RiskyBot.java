import com.google.inject.Inject;

public class RiskyBot implements Player {
    
    @Inject
    public RiskyBot() {
    }
    
    @Override
    public double makeBet(double playerMoney, double minimumBet) {
        return Math.max(playerMoney / 10, minimumBet);
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
