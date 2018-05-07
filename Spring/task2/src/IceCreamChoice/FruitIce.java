package IceCreamChoice;

import icecream.*;

public class FruitIce extends IceCream {

    private String topping;

    public FruitIce (String type, String taste, String firstElement, int NumOfFirst, String topping) {
        super(type, taste, firstElement, NumOfFirst);
        this.topping = topping;
    }

    public void setTopping(String topping) {
        this.topping = topping;
    }

    @Override
    public void printInfo() {
        super.printInfo();
        System.out.println("Please, don't forget to add topping: " + topping);
        System.out.println();
    }
}