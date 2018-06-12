import com.google.inject.Inject;

public class ShyBot implements Player {
    
    @Inject
    public ShyBot() {}
    
    @Override
    public double makeBet(double playerMoney, double minimumBet) {
        return minimumBet;
    }
    
    @Override
    public Action act(Hand hand, GameState gameState) {
        return Action.STAND;
    }
}
