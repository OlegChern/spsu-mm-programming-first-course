//
// Created by rinsler on 26.03.18.
//

#include "fruit_ice.h"


FruitIce::FruitIce(std::string name, std::string manufacturer, Ingredient juice) :
        IceCream(name, manufacturer),
        juice(juice)
{

}


std::string FruitIce::getRecipe()
{
    return "Recipe of " + name +
           " from " + manufacturer +
           ": freeze " + std::to_string(juice.weight) +
           " grams of " + juice.name +
           " juice.";
}