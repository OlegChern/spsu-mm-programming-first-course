package IceCreamImplementations;

import IceCreamAbstract.IceCream;

public class FruitIce extends IceCream {

    protected Ingredient juice;

    public FruitIce(String name, String manufacturer, Ingredient juice) {
        super(name, manufacturer);
        this.juice = juice;
    }

    @Override
    public String getRecipe() {
        return "Recipe of " + name +
                " from " + manufacturer +
                ": freeze " + juice.getWeight() +
                " grams of " + juice.getName() +
                " juice.";
    }

    public Ingredient getJuice() {
        return juice;
    }

    public void setJuice(Ingredient juice) {
        this.juice = juice;
    }
}
