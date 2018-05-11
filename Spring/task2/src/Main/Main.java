package Main;

import IceCreamChoice.*;
import icecream.*;
import java.util.ArrayList;
import java.util.List;


public class Main {

    public static void main(String[] args) {

        List <IceCream> IceCreamList = new ArrayList<>();

        IceCreamList.add(new Sundae("cookie dough",5, "caramel"));
        IceCreamList.add(new FruitIce("ice cream with fruits","strawberry"));

        for (IceCream IceCream : IceCreamList) {
            IceCream.printInfo();
        }

    }
}

