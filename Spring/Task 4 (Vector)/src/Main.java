import vector.Vector;

import java.util.ArrayList;
import java.util.HashSet;

public class Main {

    public static void main(String[] args) {
        // begin of the integers example
        Vector<Integer> integers = new Vector<>();
        integers.addAll(new ArrayList<Integer>() {{
            add(1);
            add(2);
            add(3);
            add(4);
        }});
        System.out.println("Initial state: " + integers);

        integers.removeAll(new HashSet<Integer>() {{
            add(1);
            add(4);
        }});
        System.out.println("After removing 1 and 4: " + integers);

        integers.set(0, 15);
        System.out.println("After setting 15 on the 0 position: " + integers);

        integers.add(31);
        System.out.println("After adding 31 to the end of the list: " + integers);
        // end of the integers example

        System.out.println();

        // begin of the strings example
        Vector<String> strings = new Vector<>();
        strings.addAll(new ArrayList<String>() {{
            add("Hello");
            add("I am very");
            add("glad");
            add("to see you");
        }});
        System.out.println("Initial state: " + strings);

        strings.removeAll(new HashSet<String>() {{
            add("Hello");
            add("to see you");
        }});
        System.out.println("After removing \"Hello\" and \"to see you\": " + strings);

        strings.set(0, "I won't be");
        System.out.println("After setting \"I won't be\" on the 0 position: " + strings);

        strings.add("if you leave me");
        System.out.println("After adding \"if you leave me\" to the end of the list: " + strings);
        // end of the strings example
    }
}
