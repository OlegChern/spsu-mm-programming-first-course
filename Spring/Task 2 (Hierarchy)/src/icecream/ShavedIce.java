package icecream;

import com.sun.istack.internal.Nullable;

public class ShavedIce extends MilkyIceCream {
    protected Ingredient fruitIce;

    public ShavedIce(String name, String manufacturer, Ingredient flavor, Ingredient fruitIce, @Nullable Ingredient glaze, @Nullable Ingredient syrup) {
        super(name, manufacturer, flavor, glaze, syrup);
        this.fruitIce = fruitIce;
    }

    @Override
    public String getRecipe() {
        return super.getRecipe() +
                " Add " + fruitIce.getWeight() + " grams of shaved frozen " + fruitIce.getName() + " juice.";
    }
}
