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

}
