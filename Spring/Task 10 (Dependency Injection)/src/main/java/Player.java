public interface Player {
    double makeBet(double playerMoney, double minimumBet);
    
    Action act(Hand hand, GameState gameState);
}
