package icecream;

public abstract class IceCream {

    protected String type;
    protected String taste;
    protected String firstElement;
    protected int NumOfFirst;

    public IceCream(String type, String taste, String firstElement, int NumOfFirst) {
        this.type = type;
        this.taste = taste;
        this.firstElement = firstElement;
        this.NumOfFirst = NumOfFirst;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setTaste(String taste) {
        this.taste = taste;
    }

    public void setFirstElement(String firstElement) {
        this.firstElement = firstElement;
    }

    public void setNumOfFirst(int numOfFirst) {
        NumOfFirst = numOfFirst;
    }

    private String output(int value)
    {
        if (value == 1)
            return "ball";
        else
            return "balls";
    }

    public void printInfo() {
        System.out.println("Ice Cream");
        System.out.println("Type: " + type);
        System.out.println("Taste: " + taste);
        System.out.println("To make it follow the receipe:");
        System.out.println("Add " + NumOfFirst + " " + output(NumOfFirst) + " of " + firstElement);
    }
}