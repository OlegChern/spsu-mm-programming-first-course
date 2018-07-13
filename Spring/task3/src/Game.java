public class Game {
    private Player[] players;
    private Casino casino;
    private Roulette roulette;
    private BetWorker betWorker;

    public Game(Casino casino, Roulette roulette, BetWorker betWorker) {
        this.casino = casino;
        this.roulette = roulette;
        this.betWorker = betWorker;
    }

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public void Round() {
        betWorker.setPlayers(players);
        betWorker.setBets();
        casino.setBetWorker(betWorker);
        casino.setSpinResult(roulette.spin());
        casino.payBets();
    }
}