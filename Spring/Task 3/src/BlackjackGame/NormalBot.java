package BlackjackGame;

public class NormalBot extends Player {

    public NormalBot(Integer money, Observer table) {
        super(money, table);
    }

    public void Play() {

        if (this.getScore() < 19) {
            doNotify(new GameEvent(this, EventType.HIT));
        } else {
            doNotify(new GameEvent(this, EventType.STAND));
        }
    }

    public void MakeBet() {

        if (this.getMoney() > 100) this.currentStake = 100;
        else this.currentStake = this.money;

        numberOfGames++;
    }
}
