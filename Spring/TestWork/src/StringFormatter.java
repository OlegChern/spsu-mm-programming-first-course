public class StringFormatter implements Formattable<String> {

    private String decorator;

    public StringFormatter(String decorator) {
        this.decorator = decorator;
    }

    @Override
    public String format(String value) {
        return decorator + value + decorator;
    }
}
