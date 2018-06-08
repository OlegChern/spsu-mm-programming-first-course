package Implementations;

import IceCreamLib.IceCream;

public class Eskimo extends IceCream {

    private String chocolateType;
    private String shape;
    private String wrapping;

    public Eskimo() {

        super("Eskimo", "Eskimo Pie", "Strawberry", 80, 65.95);
        chocolateType = "Milk Chocolate";
        shape = "Cylindrical";
        wrapping = "Foil";
    }

    @Override
    public String getFullInfo() {

        return (super.getFullInfo() +
                "\nChocolate type: " + chocolateType +
                "\nShape: " + shape +
                "\nWrapping: " + wrapping);
    }
}
