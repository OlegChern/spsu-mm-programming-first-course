package IceCreamAbstract;

public abstract class IceCream {

    protected String name;
    protected String manufacturer;

    public IceCream(String name, String manufacturer) {
        this.name = name;
        this.manufacturer = manufacturer;
    }

    public abstract String getRecipe();
}
