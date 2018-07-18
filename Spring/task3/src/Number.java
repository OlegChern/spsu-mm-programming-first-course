public enum Number {
    LITTLE_NUMBER(0),
    BIG_NUMBER(1);

    private int value;

    Number(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public static boolean betCheck(Bet bet, int spinResult) {
        return ((bet.getBetChoice() == Number.LITTLE_NUMBER.getValue() && spinResult <= 18) || (bet.getBetChoice() == Number.BIG_NUMBER.getValue() && spinResult > 18));

    }
}
