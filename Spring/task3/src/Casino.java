public class Casino {
    public static final int AMOUNT_OF_NUMBERS = 37;
    //if you want to add 00, just change AMOUNT_OF_NUMBERS and classify 00 as the next number after old AMOUNT_OF_NUMBERS and add it to this array
    public static final int[] NULL_NUMBERS = new int[]{0};
    private Player[] players;
    private Bet[] bets;
    private int spinResult;

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public void setBets() {
        bets = new Bet[players.length];
        for (int i = 0; i < players.length; i++) {
            Bet bet = players[i].makeBet();
            bets[i] = bet;
            players[i].payCash(bet.getSumOfBet());
        }
    }

    public void setSpinResult(int spinResult) {
        this.spinResult = spinResult;
    }

    public boolean notNull(int spinResult) {
        for (int i : NULL_NUMBERS) {
            if (spinResult == i) {
                return false;
            }
        }
        return true;
    }

    public void pay(Player player, int sum) {
        player.addCash(sum);
    }

    public void payBets() {
        int winCoef;
        if (notNull(spinResult)) {
            for (int i = 0; i < players.length; i++) {
                winCoef = Game.getWinCoef(bets[i], spinResult);
                pay(players[i], winCoef * bets[i].getSumOfBet());
            }
        }
    }
}