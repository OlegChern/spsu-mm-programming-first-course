public class Bet {

    private BetType typeOfBet;
    private int betChoice;
    private int sumOfBet;

    public Bet(BetType typeOfBet, int betChoice, int sumOfBet) {
        this.typeOfBet = typeOfBet;
        this.betChoice = betChoice;
        this.sumOfBet = sumOfBet;
    }

    public int getBetChoice() {
        return betChoice;
    }

    public BetType getTypeOfBet() {
        return typeOfBet;
    }

    public int getSumOfBet() {
        return sumOfBet;
    }
}
