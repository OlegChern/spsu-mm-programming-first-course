package BlackjackGame;

public class Dealer extends Player {

    Dealer() {
        super();
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
