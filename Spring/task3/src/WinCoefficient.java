public enum WinCoefficient {
    COLOUR(2),
    DOZEN(3),
    SIZE(2);

    private int value;

    WinCoefficient(int value) {
        this.value = value;
    }


    public int getValue() {
        return value;
    }
}
