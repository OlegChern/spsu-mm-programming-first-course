public class RiskyBot implements Player {
    @Override
    public double makeBet(double playerMoney, double minimumBet) {
        return Math.max(playerMoney / 5, minimumBet);
    }
    
    @Override
    public Action act(Hand hand, GameState gameState) {
        if (hand.isSplittable()) {
            return Action.SPLIT;
        }
    
        if (hand.getScore() < 12) {
            return Action.DOUBLE;
        }
    
        if (hand.getScore() < 16) {
            return Action.HIT;
        }
    
        return Action.STAND;
    }
}
