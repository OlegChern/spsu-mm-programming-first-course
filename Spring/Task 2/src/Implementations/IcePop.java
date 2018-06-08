package Implementations;

import IceCreamLib.IceCream;

public class IcePop extends IceCream {

    private String filling;
    private String shape;

    public IcePop() {

        super("Ice Pop", "Frozen yogurt", "Pineapple", 70, 20.99);
        shape = "Elliptic";
        filling = "Popping caramel";
    }

    @Override
    public String getFullInfo() {

        return (super.getFullInfo() +
                "\nFilling: " + filling +
                "\nShape: " + shape);
    }
}
