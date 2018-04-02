public class IntegerAddingFormatter implements Formattable<Integer> {

    private int addingValue;

    public IntegerAddingFormatter(int addingValue) {
        this.addingValue = addingValue;
    }

    @Override
    public String format(Integer value) {
        return Integer.toString(value + addingValue);
    }
}
