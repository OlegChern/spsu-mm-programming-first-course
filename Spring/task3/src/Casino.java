public class Casino {
    public static final int COLOUR_WIN_COEF = 2;
    public static final int DOZEN_WIN_COEF = 3;
    public static final int SIZE_WIN_COEF = 2;
    public static final int ONE_NUMBER_WIN_COEF = 36;
    public static final int AMOUNT_OF_NUMBERS = 37;
    public static final int[] NULL_NUMBERS = new int[]{0}; //if you want to add 00, just change AMOUNT_OF_NUMBERS and classify 00 as the next number after old AMOUNT_OF_NUMBERS and add it to this array
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
                    case Bet.BET_ON_COLOUR:
                        if ((bets[i].getBetChoice() == Bet.RED_BET && isRed(spinResult)) || (bets[i].getBetChoice() == Bet.BLACK_BET && isBlack(spinResult))) {
                            pay(players[i], bets[i].getSumOfBet() * COLOUR_WIN_COEF);
                        }
                        break;
                    case Bet.BET_ON_DOZEN:
                        if ((bets[i].getBetChoice() == Bet.FIRST_DOZEN_BET && spinResult <= 12) || (bets[i].getBetChoice() == Bet.SECOND_DOZEN_BET && spinResult > 12 && spinResult <= 24) || (bets[i].getBetChoice() == Bet.THIRD_DOZEN_BET && spinResult > 24)) {
                            pay(players[i], bets[i].getSumOfBet() * DOZEN_WIN_COEF);
                        }
                        break;
                    case Bet.BET_ON_SIZE:
                        if ((bets[i].getBetChoice() == Bet.LITTLE_NUMBER_BET && spinResult <= 18) || (bets[i].getBetChoice() == Bet.BIG_NUMBER_BET && spinResult > 18)) {
                            pay(players[i], bets[i].getSumOfBet() * SIZE_WIN_COEF);
                        }
                        break;
                    case Bet.BET_ON_NUMBER:
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