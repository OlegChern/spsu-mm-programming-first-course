public class CleverBot extends Player {
    private int oldCash;
    private int count;
    public static final int CLEVER_BOT_BET = 10;

    public CleverBot(int cash) {
        this.cash = cash;
        oldCash = cash;
        count = 1;
    }

    public Bet makeBet() {
        if (oldCash > cash) {
            count *= 2;
        } else {
            count = 1;
        }
        oldCash = cash;
        return new Bet(Bet.BET_ON_COLOUR, Bet.RED_BET, CLEVER_BOT_BET * count);
    }
}