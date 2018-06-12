package IceCreamImplementations;

import com.sun.istack.internal.Nullable;
import IceCreamAbstract.IceCream;

public class MilkyIceCream extends IceCream {
    protected Ingredient flavor;
    protected Ingredient glaze;
    protected Ingredient syrup;

    public MilkyIceCream(String name, String manufacturer, Ingredient flavor, @Nullable Ingredient glaze, @Nullable Ingredient syrup) {
        super(name, manufacturer);
        this.flavor = flavor;
        this.glaze = glaze;
        this.syrup = syrup;
    }

    @Override
    public String getRecipe() {
        String recipe =
                "Recipe of " + name +
                        " from " + manufacturer +
                        ": blend milk, egg yolk, cream, sugar and " +
                        flavor.getWeight() + " grams of " + flavor.getName() +
                        " and then whip and freeze it.";

        if (syrup != null) {
            recipe += " Pour all with " + syrup.getWeight() + " grams of " + syrup.getName() + ".";
        }
        if (glaze != null) {
            recipe += " Finally, cover product with " + glaze.getWeight() + " grams of " + glaze.getName() +
                    " and then immediately freeze it.";
        }

        return recipe;
    }
}
