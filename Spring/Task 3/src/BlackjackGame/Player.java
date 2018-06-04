package BlackjackGame;

import java.util.ArrayList;

public abstract class Player implements Subject {

    public ArrayList<Card> hand;

    protected Integer numberOfGames;
    protected Integer money;
    protected Integer currentStake;

    protected Observer gameTable;

    public Player(Integer money, Observer table) {

        this.money = money;
        this.addObserver(table);
        this.currentStake = 0;
        this.hand = new ArrayList<>();
        this.numberOfGames = 0;
    }

    public Integer getCurrentStake() {
        return currentStake;
    }

    public void winMoney(Integer money) {
        this.money += money;
    }

    public void loseMoney(Integer money) {
        this.money -= money;
    }

    public Integer getMoney() {
        return this.money;
    }

    public void clearHand() {
        this.hand.clear();
    }

    public Integer getScore() {
        int result = 0;
        boolean isAce = false;

        for (Card card : hand) {
            result += card.getValue();
            if (card.getRank() == Ranks.Ace) isAce = true;
        }

        if (isAce && result + 10 <= 21) result += 10;

        return result;
    }

    public String getStatistic(String name) {
        return ("After " + numberOfGames + " games " + name + "'s account is " + money);
    }

    public void doubleDown() {
        currentStake *= 2;
    }

    @Override
    public void doNotify(GameEvent event) {
        gameTable.onNotify(event);
    }

    @Override
    public void addObserver(Observer observer) {

        gameTable = observer;
    }

    abstract public void MakeBet();

    abstract public void Play();
}
