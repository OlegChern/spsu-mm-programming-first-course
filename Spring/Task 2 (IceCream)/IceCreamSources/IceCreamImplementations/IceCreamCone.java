package IceCreamImplementations;

import com.sun.istack.internal.Nullable;

public class IceCreamCone extends MilkyIceCream {
    protected Ingredient cone;

    public IceCreamCone(String name, String manufacturer, Ingredient flavor, Ingredient cone, @Nullable Ingredient glaze, @Nullable Ingredient syrup) {
        super(name, manufacturer, flavor, glaze, syrup);
        this.cone = cone;
    }

    @Override
    public String getRecipe() {
        return super.getRecipe() +
                " Put it to the " + cone.getWeight() + "-gram " + cone.getName() + ".";
    }
}
