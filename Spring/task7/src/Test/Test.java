package Test;

public class Test {
    private int n;

    public Test(int n) {
        this.n = n;
    }

    @Override
    public String toString() {
        return "Tested object{" + n + "}";
    }

}