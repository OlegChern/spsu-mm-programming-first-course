#include <iostream>
#include <vector>

#include "ice_cream/ice_cream.h"
#include "ice_cream/fruit_ice/fruit_ice.h"
#include "ice_cream/milky_ice_cream/milky_ice_cream.h"
#include "ice_cream/milky_ice_cream/ice_cream_cone/ice_cream_cone.h"
#include "ice_cream/milky_ice_cream/shaved_ice/shaved_ice.h"


int main()
{
    using namespace std;

    std::vector<IceCream *> iceCreams(4);

    iceCreams[0] = new FruitIce("Orange Fruity", "Happy IceCream Inc.", {"orange", 200});

    iceCreams[1] = new MilkyIceCream("Creme Brulee in white chocolate", "Milky Nightmare Corp.",
                                     {"creme Brulee", 200}, {"white chocolate", 30});

    iceCreams[2] = new IceCreamCone("Cherry ice cream in waffle cup under milk chocolate and cherry syrup",
                                    "Awesome sweets (c)", {"cherry", 200},
                                    {"waffle cup", 20}, {"milk chocolate", 20}, {"cherry", 20});

    iceCreams[3] = new ShavedIce("Mango ice cream with melon ice", "Ice Ice Baby Industries",
                                 {"mango", 100}, {"melon", 100});

    for (int i = 0; i < 4; ++i) {
        cout << iceCreams[i]->getRecipe() << '\n';
        delete iceCreams[i];
    }

    return 0;
}