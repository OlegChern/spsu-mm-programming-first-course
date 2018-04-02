package com.company;

public class Format {
    public String format(int value, int addition)
    {
        if (value % 2 == 0) {
            value += addition;
            System.out.print("U entered an even number. So the result is ");
        }
        else {
            value -= addition;
            System.out.print("U entered uneven number. So the result is ");
        }
        return Integer.toString(value);
    }
    public String format (String value, String addition)
    {
        if (value.length() > 5) {
            value = addition + value + addition;
            System.out.print("Your string consists of min 6 characters. So the result is ");
        }
        else {
            value = value + addition + value;
            System.out.print("Your string is short. So the result is ");
        }
        return value;
    }
}
