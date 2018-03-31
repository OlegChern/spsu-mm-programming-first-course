//
// Created by rinsler on 30.03.18.
//

#include "shaved_ice.h"

ShavedIce::ShavedIce(
        std::string name,
        std::string manufacturer,
        Ingredient flavor,
        Ingredient fruitIce,
        Ingredient glaze,
        Ingredient syrup
) :
        MilkyIceCream(name, manufacturer, flavor, glaze, syrup),
        fruitIce(fruitIce)
{

}

std::string ShavedIce::getRecipe()
{
    return MilkyIceCream::getRecipe() +
           " Add " + std::to_string(fruitIce.weight) + " grams of frozen " + fruitIce.name + " juice.";
}
