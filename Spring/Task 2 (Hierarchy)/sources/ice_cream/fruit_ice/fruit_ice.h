//
// Created by rinsler on 26.03.18.
//

#ifndef TASK_2_HIERARCHY_FRUITICE_H
#define TASK_2_HIERARCHY_FRUITICE_H

#include "../ice_cream.h"
#include "../../ingredient/ingredient.h"


class FruitIce : public IceCream
{

public:

    FruitIce(std::string name, std::string manufacturer, Ingredient juice);

    std::string getRecipe() override;

protected:

    Ingredient juice;
};


#endif //TASK_2_HIERARCHY_FRUITICE_H
