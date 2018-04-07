import icecream.*;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<IceCream> iceCreamsList = new ArrayList<>();

        iceCreamsList.add(new FruitIce(
                "Orange Fruity",
                "Happy IceCream Inc.",
                new Ingredient("orange", 200))
        );

        iceCreamsList.add(new MilkyIceCream(
                "Creme Brulee in white chocolate",
                "Milky Nightmare Corp.",
                new Ingredient("creme Brulee", 200),
                new Ingredient("white chocolate", 30),
                null)
        );

        iceCreamsList.add(new IceCreamCone(
                "Cherry ice cream in waffle cup under milk chocolate and cherry syrup",
                "Awesome sweets (c)",
                new Ingredient("cherry", 200),
                new Ingredient("waffle cup", 20),
                new Ingredient("milk chocolate", 20),
                new Ingredient("cherry", 20))
        );

        iceCreamsList.add(new ShavedIce(
                "Mango ice cream with melon ice",
                "Ice Ice Baby Industries",
                new Ingredient("mango", 100),
                new Ingredient("melon", 100),
                null,
                null)
        );

        for (IceCream iceCream : iceCreamsList) {
            System.out.println(iceCream.getRecipe());
        }

    }
}
