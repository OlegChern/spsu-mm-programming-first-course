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
}
