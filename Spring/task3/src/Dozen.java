public enum Dozen {

    FIRST_DOZEN(0),
    SECOND_DOZEN(1),
    THIRD_DOZEN(2);

    private int value;

    Dozen(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public static boolean betCheck(Bet bet, int spinResult) {
        return ((bet.getBetChoice() == Dozen.FIRST_DOZEN.getValue() && spinResult <= 12) || (bet.getBetChoice() == Dozen.SECOND_DOZEN.getValue() && spinResult > 12 && spinResult <= 24) || (bet.getBetChoice() == Dozen.THIRD_DOZEN.getValue() && spinResult > 24));
    }
}
