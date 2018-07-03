public class Game {
    public static final int RED_BET = 0;
    public static final int BLACK_BET = 1;
    public static final int FIRST_DOZEN_BET = 0;
    public static final int SECOND_DOZEN_BET = 1;
    public static final int THIRD_DOZEN_BET = 2;
    public static final int LITTLE_NUMBER_BET = 0;
    public static final int BIG_NUMBER_BET = 1;
    public static final int COLOUR_WIN_COEF = 2;
    public static final int DOZEN_WIN_COEF = 3;
    public static final int SIZE_WIN_COEF = 2;
    public static final int ONE_NUMBER_WIN_COEF = 36;
    public static final int BET_ON_COLOUR = 1;
    public static final int BET_ON_DOZEN = 2;
    public static final int BET_ON_SIZE = 3;
    public static final int BET_ON_NUMBER = 4;
    public static final int SILLY_BOT_BET = 20;
    public static final int CLEVER_BOT_BET = 10;

    private Player[] players;
    private Casino casino;
    private Roulette roulette;

    public Game(Casino casino, Roulette roulette) {
        this.casino = casino;
        this.roulette = roulette;
    }

    public  void setPlayers(Player[] players) {
        this.players = players;
    }

    public void Round() {
        casino.setPlayers(players);
        casino.setBets();
        casino.setSpinResult(roulette.spin());
        casino.payBets();
    }
}