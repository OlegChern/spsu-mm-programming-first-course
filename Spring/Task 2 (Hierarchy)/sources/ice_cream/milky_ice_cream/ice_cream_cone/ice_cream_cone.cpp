//
// Created by rinsler on 27.03.18.
//

#include "ice_cream_cone.h"


IceCreamCone::IceCreamCone(
        std::string name,
        std::string manufacturer,
        Ingredient flavor,
        Ingredient cone,
        Ingredient glaze,
        Ingredient syrup
) :
        MilkyIceCream(name, manufacturer, flavor, glaze, syrup),
        cone(cone)
{

}

std::string IceCreamCone::getRecipe()
{
    return MilkyIceCream::getRecipe() +
           " Put it to the " + std::to_string(cone.weight) + "-gram " + cone.name + ".";
}
