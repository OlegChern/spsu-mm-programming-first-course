package IceCreamLib;

public class Cornet extends IceCream {

    private String chocolateType;
    private String coneType;

    public Cornet() {

        super("Sugar Cone", "Cornet", "Vanilla", 70, 29.99);
        chocolateType = "Milk Chocolate";
        coneType = "Waffle";

    }

    @Override
    public String getFullInfo() {

        return (super.getFullInfo() +
                "\nChocolate type: " + chocolateType +
                "\nCone type: " + coneType);
    }
}
