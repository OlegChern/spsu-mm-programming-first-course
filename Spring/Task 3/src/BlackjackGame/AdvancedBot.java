package BlackjackGame;

public class AdvancedBot extends Player {

    public AdvancedBot(Integer money, Observer table) {
        super(money, table);
    }

    @Override
    public void Play() {

        if(this.getScore() == 11) {
            doNotify(new GameEvent(this, EventType.DOUBLE));
        }
        else if (this.hand.size() == 2 && this.getScore() < 5) {
            doNotify(new GameEvent(this, EventType.SURRENDER));
        }
        else if (this.getScore() < 16) {
            doNotify(new GameEvent(this, EventType.HIT));
        }
        else doNotify(new GameEvent(this, EventType.STAND));
    }

    @Override
    public void MakeBet() {
        if (this.money > 1000) this.currentStake = 500;
        else if (this.money > 500) this.currentStake = 150;
        else if (this.money > 250) this.currentStake = 100;
        else if (this.money > 50) this.currentStake = 50;
        else this.currentStake = this.money;

        numberOfGames++;
    }
}
