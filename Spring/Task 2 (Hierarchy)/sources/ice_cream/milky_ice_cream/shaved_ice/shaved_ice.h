//
// Created by rinsler on 30.03.18.
//

#ifndef TASK_2_HIERARCHY_SHAVED_ICE_H
#define TASK_2_HIERARCHY_SHAVED_ICE_H


#include "../milky_ice_cream.h"


class ShavedIce : public MilkyIceCream
{
public:
    ShavedIce(
            std::string name,
            std::string manufacturer,
            Ingredient flavor,
            Ingredient fruitIce,
            Ingredient glaze = {},
            Ingredient syrup = {}
    );

    std::string getRecipe() override;

protected:
    Ingredient fruitIce;
};


#endif //TASK_2_HIERARCHY_SHAVED_ICE_H
