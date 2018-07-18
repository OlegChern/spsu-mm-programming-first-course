public class Casino {
    public static final int ONE_NUMBER_WIN_COEF = 36;
    public static final int AMOUNT_OF_NUMBERS = 37;
    //if you want to add 00, just change AMOUNT_OF_NUMBERS and classify 00 as the next number after old AMOUNT_OF_NUMBERS and add it to this array
    public static final int[] NULL_NUMBERS = new int[]{0};
    private Player[] players;
    private Bet[] bets;
    private int spinResult;
    private BetWorker betWorker;

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public void setBetWorker(BetWorker betWorker) {
        this.betWorker = betWorker;
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

    public void payBets() {
        int winCoef;
        if (notNull(spinResult)) {
            for (int i = 0; i < betWorker.getNumOfPlayers(); i++) {
                winCoef = getWinCoef(betWorker.getBet(i), spinResult);
                betWorker.pay(i, winCoef);
            }
        }
    }

    public int getWinCoef (Bet bet, int spinResult) {
        switch (bet.getTypeOfBet()) {
            case ON_COLOUR:
                if (Colour.betCheck(bet, spinResult)) {
                    return WinCoefficient.COLOUR.getValue();
                }
                break;
            case ON_DOZEN:
                if (Dozen.betCheck(bet, spinResult)) {
                    return WinCoefficient.DOZEN.getValue();
                }
                break;
            case ON_SIZE:
                if (Number.betCheck(bet, spinResult)) {
                    return WinCoefficient.SIZE.getValue();
                }
                break;
            case ON_NUMBER:
                if (checkNumberBet(bet, spinResult)) {
                    return ONE_NUMBER_WIN_COEF;
                }
                break;
        }
        return 0;
    }

    public boolean checkNumberBet (Bet bet, int spinResult) {
        return (bet.getBetChoice() == spinResult);
    }
}