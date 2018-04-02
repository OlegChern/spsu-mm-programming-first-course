public class IntegerMultiplyingFormatter implements Formattable<Integer> {

    private int multiplyingValue;

    public IntegerMultiplyingFormatter(int multiplyingValue) {
        this.multiplyingValue = multiplyingValue;
    }

    @Override
    public String format(Integer value) {
        return Integer.toString(value * multiplyingValue);
    }
}
