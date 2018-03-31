//
// Created by rinsler on 26.03.18.
//

#ifndef TASK_2_HIERARCHY_ICE_CREAM_H
#define TASK_2_HIERARCHY_ICE_CREAM_H

#include <string>


class IceCream
{
public:
    IceCream(std::string name, std::string manufacturer);

    virtual ~IceCream() = default;

    virtual std::string getRecipe() = 0;

protected:
    std::string name;
    std::string manufacturer;
};


#endif //TASK_2_HIERARCHY_ICE_CREAM_H
