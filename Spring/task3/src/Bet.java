public class Bet {
    public static final int RED_BET = 0;
    public static final int BLACK_BET = 1;
    public static final int FIRST_DOZEN_BET = 0;
    public static final int SECOND_DOZEN_BET = 1;
    public static final int THIRD_DOZEN_BET = 2;
    public static final int LITTLE_NUMBER_BET = 0;
    public static final int BIG_NUMBER_BET = 1;
    public static final int BET_ON_COLOUR = 1;
    public static final int BET_ON_DOZEN = 2;
    public static final int BET_ON_SIZE = 3;
    public static final int BET_ON_NUMBER = 4;

    private int typeOfBet;
    private int betChoice;
    private int sumOfBet;

    public Bet(int typeOfBet, int betChoice, int sumOfBet) {
        this.typeOfBet = typeOfBet;
        this.betChoice = betChoice;
        this.sumOfBet = sumOfBet;
    }

    public int getBetChoice() {
        return betChoice;
    }

    public int getTypeOfBet() {
        return typeOfBet;
    }

    public int getSumOfBet() {
        return sumOfBet;
    }
}
