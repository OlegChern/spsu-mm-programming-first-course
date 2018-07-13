public class Casino {
    public static final int ONE_NUMBER_WIN_COEF = 36;
    public static final int AMOUNT_OF_NUMBERS = 37;
    //if you want to add 00, just change AMOUNT_OF_NUMBERS and classify 00 as the next number after old AMOUNT_OF_NUMBERS and add it to this array
    public static final int[] NULL_NUMBERS = new int[]{0};
    private int spinResult;
    private BetWorker betWorker;

    public void setBetWorker(BetWorker betWorker) {
        this.betWorker = betWorker;
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

    public boolean isRed(int spinResult) {
        return (spinResult % 2 != 0);
    }

    public boolean isBlack(int spinResult) {
        return (spinResult % 2 == 0);
    }

    public void payBets() {
        if (notNull(spinResult)) {
            for (int i = 0; i < betWorker.getNumOfPlayers(); i++) {
                switch (betWorker.getTypeOfBet(i)) {
                    case ON_COLOUR:
                        if ((betWorker.getBetChoice(i) == Colour.RED.getValue() && isRed(spinResult)) || (betWorker.getBetChoice(i) == Colour.BLACK.getValue() && isBlack(spinResult))) {
                            betWorker.pay(i, WinCoefficient.COLOUR.getValue());
                        }
                        break;
                    case ON_DOZEN:
                        if ((betWorker.getBetChoice(i) == Dozen.FIRST_DOZEN.getValue() && spinResult <= 12) || (betWorker.getBetChoice(i) == Dozen.SECOND_DOZEN.getValue() && spinResult > 12 && spinResult <= 24) || (betWorker.getBetChoice(i) == Dozen.THIRD_DOZEN.getValue() && spinResult > 24)) {
                            betWorker.pay(i, WinCoefficient.DOZEN.getValue());
                        }
                        break;
                    case ON_SIZE:
                        if ((betWorker.getBetChoice(i) == Number.LITTLE_NUMBER.getValue() && spinResult <= 18) || (betWorker.getBetChoice(i) == Number.BIG_NUMBER.getValue() && spinResult > 18)) {
                            betWorker.pay(i, WinCoefficient.SIZE.getValue());
                        }
                        break;
                    case ON_NUMBER:
                        if (betWorker.getBetChoice(i) == spinResult) {
                            betWorker.pay(i, ONE_NUMBER_WIN_COEF);
                        }
                        break;
                }
            }
        }
    }
}