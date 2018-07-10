public class Casino {
    public static final int ONE_NUMBER_WIN_COEF = 36;
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

    public boolean isRed(int spinResult) {
        return (spinResult % 2 != 0);
    }

    public boolean isBlack(int spinResult) {
        return (spinResult % 2 == 0);
    }

    public void payBets() {
        if (notNull(spinResult)) {
            for (int i = 0; i < bets.length; i++) {
                switch (bets[i].getTypeOfBet()) {
                    case ON_COLOUR:
                        if ((bets[i].getBetChoice() == Colour.RED.getValue() && isRed(spinResult)) || (bets[i].getBetChoice() == Colour.BLACK.getValue() && isBlack(spinResult))) {
                            pay(players[i], bets[i].getSumOfBet() * WinCoefficient.COLOUR.getValue());
                        }
                        break;
                    case ON_DOZEN:
                        if ((bets[i].getBetChoice() == Dozen.FIRST_DOZEN.getValue() && spinResult <= 12) || (bets[i].getBetChoice() == Dozen.SECOND_DOZEN.getValue() && spinResult > 12 && spinResult <= 24) || (bets[i].getBetChoice() == Dozen.THIRD_DOZEN.getValue() && spinResult > 24)) {
                            pay(players[i], bets[i].getSumOfBet() * WinCoefficient.DOZEN.getValue());
                        }
                        break;
                    case ON_SIZE:
                        if ((bets[i].getBetChoice() == Number.LITTLE_NUMBER.getValue() && spinResult <= 18) || (bets[i].getBetChoice() == Number.BIG_NUMBER.getValue() && spinResult > 18)) {
                            pay(players[i], bets[i].getSumOfBet() * WinCoefficient.SIZE.getValue());
                        }
                        break;
                    case ON_NUMBER:
                        if (bets[i].getBetChoice() == spinResult) {
                            pay(players[i], bets[i].getSumOfBet() * ONE_NUMBER_WIN_COEF);
                        }
                        break;
                }
            }
        }
    }

    public void pay(Player player, int sum) {
        player.addCash(sum);
    }
}