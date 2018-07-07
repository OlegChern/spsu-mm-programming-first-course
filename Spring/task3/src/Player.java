public abstract class Player {
    protected int cash;

    public int showCash() {
        return cash;
    }

    public void addCash(int sum) {
        cash += sum;
    }

    public void payCash(int sum) {
        cash -= sum;
    }

    public abstract Bet makeBet();
}
