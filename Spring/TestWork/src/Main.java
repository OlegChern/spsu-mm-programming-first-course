import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final int intExample = 22;
    private static final String stringExample = "I love programming";

    private static <T extends Formattable<V>, V> void print(List<T> formatters, V value) {
        for (Formattable<V> formatter : formatters) {
            System.out.println(formatter.format(value));
        }
    }

    public static void main(String[] args) {

        List<Formattable<Integer>> integerFormatters = new ArrayList<>();
        integerFormatters.add(new IntegerAddingFormatter(10));
        integerFormatters.add(new IntegerAddingFormatter(-10));
        integerFormatters.add(new IntegerMultiplyingFormatter(10));
        integerFormatters.add(new IntegerMultiplyingFormatter(-10));

        System.out.println("Initial value: " + intExample);
        print(integerFormatters, intExample);

        System.out.println();

        List<Formattable<String>> stringFormatters = new ArrayList<>();
        stringFormatters.add(new StringFormatter("^.^"));
        stringFormatters.add(new StringFormatter(" ☺ "));
        stringFormatters.add(new StringFormatter(" ❤ "));

        System.out.println("Initial value: " + stringExample);
        print(stringFormatters, stringExample);
    }
}
