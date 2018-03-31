//
// Created by rinsler on 30.03.18.
//

#ifndef TASK_2_HIERARCHY_INGRIDIENT_H
#define TASK_2_HIERARCHY_INGRIDIENT_H

#include <string>


struct Ingredient
{
    std::string name;
    unsigned int weight{};

    Ingredient() = default;

    Ingredient(std::string name, unsigned int weight);
};


#endif //TASK_2_HIERARCHY_INGRIDIENT_H
