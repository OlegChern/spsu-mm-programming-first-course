public enum  Colour {
    RED(0),
    BLACK(1);

    private int value;

    Colour(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public static boolean isRed(int spinResult) {
        return (spinResult % 2 != 0);
    }

    public static boolean isBlack(int spinResult) {
        return (spinResult % 2 == 0);
    }

    public static boolean betCheck(Bet bet, int spinResult) {
        return  ((bet.getBetChoice() == Colour.RED.getValue() && isRed(spinResult)) || (bet.getBetChoice() == Colour.BLACK.getValue() && isBlack(spinResult)));
    }
}
