package BlackjackGame;

public class Dealer extends Player {

    Dealer(Observer table) {
        super(Integer.MAX_VALUE, table);
    }

    public void Play() {

        if (this.getScore() < 16) {
            doNotify(new GameEvent(this, EventType.HIT));
        } else {
            doNotify(new GameEvent(this, EventType.DEALERFINISH));
        }
    }

    public void MakeBet() {
        this.currentStake = 0;
    }
}
