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
}
