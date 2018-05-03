package com.company;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        com.company.Format format = new com.company.Format();
        int value, addition;
        String[] string;
        System.out.println("Please input a string or a number u'd like to format and through space the relevant number or string:");
        System.out.println("P.S. don't push Enter");
        Scanner in = new Scanner(System.in);
        String input = in.nextLine();
        string = input.split(" ");
        try {
            value = Integer.parseInt(string[0]);
            addition = Integer.parseInt(string[1]);
            System.out.println(format.format(value, addition));
        }
        catch (Exception e)
        {
            System.out.println(format.format(string[0], string[1]));
        }
        // format.format();
    }
}

