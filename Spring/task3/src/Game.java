public class Game {
    private Player[] players;
    private Casino casino;
    private Roulette roulette;

    public Game(Casino casino, Roulette roulette) {
        this.casino = casino;
        this.roulette = roulette;
    }

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public void Round() {
        casino.setPlayers(players);
        casino.setBets();
        casino.setSpinResult(roulette.spin());
        casino.payBets();
    }
}