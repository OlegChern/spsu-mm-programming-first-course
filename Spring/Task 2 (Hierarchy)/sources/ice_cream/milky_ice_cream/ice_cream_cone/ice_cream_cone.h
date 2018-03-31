//
// Created by rinsler on 27.03.18.
//

#ifndef TASK_2_HIERARCHY_ICE_CREAM_CONE_H
#define TASK_2_HIERARCHY_ICE_CREAM_CONE_H


#include "../milky_ice_cream.h"


class IceCreamCone : public MilkyIceCream
{
public:
    IceCreamCone(
            std::string name,
            std::string manufacturer,
            Ingredient flavor,
            Ingredient cone,
            Ingredient glaze = {},
            Ingredient syrup = {}
    );

    std::string getRecipe() override;

protected:
    Ingredient cone;
};


#endif //TASK_2_HIERARCHY_ICE_CREAM_CONE_H
