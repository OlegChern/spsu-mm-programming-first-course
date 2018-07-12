public class Casino {
    public static final int ONE_NUMBER_WIN_COEF = 36;
    public static final int AMOUNT_OF_NUMBERS = 37;
    //if you want to add 00, just change AMOUNT_OF_NUMBERS and classify 00 as the next number after old AMOUNT_OF_NUMBERS and add it to this array
    public static final int[] NULL_NUMBERS = new int[]{0};
    private Player[] players;
    private Bet[] bets;
    private int spinResult;
    private int coef;

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

    public boolean isRed(int spinResult) {
        return (spinResult % 2 != 0);
    }

    public boolean isBlack(int spinResult) {
        return (spinResult % 2 == 0);
    }

    public int BetsCoefficient(Bet bet) {
        if (notNull(spinResult)) {
                switch (bet.getTypeOfBet()) {
                    case ON_COLOUR:
                        if ((bet.getBetChoice() == Colour.RED.getValue() && isRed(spinResult)) || (bet.getBetChoice() == Colour.BLACK.getValue() && isBlack(spinResult))) {
                            coef =  WinCoefficient.COLOUR.getValue();
                        }
                        break;
                    case ON_DOZEN:
                        if ((bet.getBetChoice() == Dozen.FIRST_DOZEN.getValue() && spinResult <= 12) || (bet.getBetChoice() == Dozen.SECOND_DOZEN.getValue() && spinResult > 12 && spinResult <= 24) || (bet.getBetChoice() == Dozen.THIRD_DOZEN.getValue() && spinResult > 24)) {
                            coef = WinCoefficient.DOZEN.getValue();
                        }
                        break;
                    case ON_SIZE:
                        if ((bet.getBetChoice() == Number.LITTLE_NUMBER.getValue() && spinResult <= 18) || (bet.getBetChoice() == Number.BIG_NUMBER.getValue() && spinResult > 18)) {
                            coef = WinCoefficient.SIZE.getValue();
                        }
                        break;
                    case ON_NUMBER:
                        if (bet.getBetChoice() == spinResult) {
                            coef =  ONE_NUMBER_WIN_COEF;
                        }
                        break;
                }
            }
        return coef;
    }
}