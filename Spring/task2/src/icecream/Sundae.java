package icecream;

public class Sundae extends IceCream {

    private String syrup;
    private String secondElement;
    private int NumOfSecond;

    public Sundae(String type, String taste, String firstElement, String secondElement, int NumOfFirst, int NumOfSecond, String syrup) {
        super(type, taste, firstElement, NumOfFirst);
        this.secondElement = secondElement;
        this.NumOfSecond = NumOfSecond;
        this.syrup = syrup;
    }

    public void setSecondElement(String secondElement) {
        this.secondElement = secondElement;
    }

    public void setNumOfSecond(int numOfSecond) {
        NumOfSecond = numOfSecond;
    }

    public void setSyrup(String syrup) {
        this.syrup = syrup;
    }

    private String piece(int value)
    {
        if (value == 1)
            return "piece";
        else
            return "pieces";
    }

    @Override
    public void printInfo() {
        super.printInfo();
        System.out.println("And add " + + NumOfSecond + " " + piece(NumOfSecond) + " of " + secondElement);
        System.out.println("Please, don't forget to add syrup: " + syrup);
        System.out.println();
    }
}
