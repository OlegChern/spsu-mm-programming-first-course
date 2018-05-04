import icecream.*;
//import IceCreamImplementation.*;

public class Main {

    public static void main(String[] args) {
        Sundae CookieDoughSundae = new Sundae("original recipe","cookie dough", "vanilla ice cream",
                "cookie dough", 2, 1, "caramel");
        CookieDoughSundae.printInfo();

        FruitIce originalFruitIce = new FruitIce("ice cream with fruits","strawberry",
                "strawberry fruit ice",3, "whipping cream");

        originalFruitIce.printInfo();

    }
}

