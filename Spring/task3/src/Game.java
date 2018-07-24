public class Game {
    private Player[] players;
    private Casino casino;
    private Roulette roulette;
    public static final int ONE_NUMBER_WIN_COEF = 36;

    public Game(Casino casino, Roulette roulette) {
        this.casino = casino;
        this.roulette = roulette;
    }

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public static int getWinCoef (Bet bet, int spinResult) {
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


    public static boolean checkNumberBet(Bet bet, int spinResult) {
        return (bet.getBetChoice() == spinResult);
    }

    public void round() {
        casino.setPlayers(players);
        casino.setBets();
        casino.setSpinResult(roulette.spin());
        casino.payBets();
    }

}