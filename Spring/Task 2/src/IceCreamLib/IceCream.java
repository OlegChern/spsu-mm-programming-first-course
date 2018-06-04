package IceCreamLib;

public abstract class IceCream {

    protected String name;
    protected String type;
    protected String flavour;
    protected Integer weight;
    protected Double price;

    protected IceCream(String name, String type, String flavour, Integer weight, Double price) {

        this.name = name;
        this.type = type;
        this.flavour = flavour;
        this.weight = weight;
        this.price = price;
    }

    public String getFullInfo() {

        return ("Name: " + name +
                "\nType: " + type +
                "\nFlavour: " + flavour +
                "\nWeight: " + weight.toString() + " grams" +
                "\nPrice (rubles): " + price.toString());
    }

}
