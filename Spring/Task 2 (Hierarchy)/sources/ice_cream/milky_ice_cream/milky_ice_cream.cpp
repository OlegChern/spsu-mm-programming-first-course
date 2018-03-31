//
// Created by rinsler on 27.03.18.
//

#include "milky_ice_cream.h"


MilkyIceCream::MilkyIceCream(
        std::string name,
        std::string manufacturer,
        Ingredient flavor,
        Ingredient glaze,
        Ingredient syrup
) :
        IceCream(name, manufacturer),
        flavor(flavor),
        glaze(glaze),
        syrup(syrup)
{

}

std::string MilkyIceCream::getRecipe()
{
    std::string recipe =
            "Recipe of " + name +
            " from " + manufacturer +
            ": blend milk, egg yolk, cream, sugar and " +
            std::to_string(flavor.weight) + " grams of " + flavor.name +
            " and then whip and freeze it.";

    if (!syrup.name.empty()) {
        recipe += " Pour all with " + std::to_string(syrup.weight) + " grams of " + syrup.name + ".";
    }
    if (!glaze.name.empty()) {
        recipe += " Finally, cover product with " + std::to_string(glaze.weight) + " grams of " + glaze.name +
                  " and then immediately freeze it.";
    }

    return recipe;
}