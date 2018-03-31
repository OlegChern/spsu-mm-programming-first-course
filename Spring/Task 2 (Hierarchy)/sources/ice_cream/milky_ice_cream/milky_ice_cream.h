//
// Created by rinsler on 27.03.18.
//

#ifndef TASK_2_HIERARCHY_CREAMY_ICE_CREAM_H
#define TASK_2_HIERARCHY_CREAMY_ICE_CREAM_H


#include "../ice_cream.h"
#include "../../ingredient/ingredient.h"


class MilkyIceCream : public IceCream
{
public:
    MilkyIceCream(
            std::string name,
            std::string manufacturer,
            Ingredient flavor,
            Ingredient glaze = {},
            Ingredient syrup = {}
    );

    std::string getRecipe() override;

protected:
    Ingredient flavor;
    Ingredient glaze;
    Ingredient syrup;
};


#endif //TASK_2_HIERARCHY_CREAMY_ICE_CREAM_H
