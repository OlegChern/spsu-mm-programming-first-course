import java.util.Random;

public class SillyBot extends Player {
    public static final int SILLY_BOT_BET = 20;

    public SillyBot(int cash) {
        this.cash = cash;
    }

    public Bet makeBet() {
        Random random = new Random();
        return new Bet(Bet.BET_ON_NUMBER, random.nextInt(Casino.AMOUNT_OF_NUMBERS), SILLY_BOT_BET);
    }
}
