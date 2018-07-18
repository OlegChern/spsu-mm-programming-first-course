public class BetWorker {

    private Player[] players;
    private Bet[] bets;

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public Bet[] getBets() {
        return bets;
    }

    public int getNumOfPlayers() {
        return players.length;
    }

    public int getBetChoice(int numOfPlayer) {
        return bets[numOfPlayer].getBetChoice();
    }

    public BetType getTypeOfBet(int numOfPlayer) {
        return bets[numOfPlayer].getTypeOfBet();
    }

    public Bet getBet(int numOfPlayer) {
        return bets[numOfPlayer];
    }

    public void setBets() {
        bets = new Bet[players.length];
        for (int i = 0; i < players.length; i++) {
            Bet bet = players[i].makeBet();
            bets[i] = bet;
            players[i].payCash(bet.getSumOfBet());
        }
    }

    public void pay(int numOfPlayer, int coef) {
        int sum = bets[numOfPlayer].getSumOfBet() * coef;
        players[numOfPlayer].addCash(sum);
    }
}
