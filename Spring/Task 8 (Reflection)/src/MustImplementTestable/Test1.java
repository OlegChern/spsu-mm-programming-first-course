package MustImplementTestable;

import TestInterface.Testable;

public class Test1 implements Testable {
    char someInterestingMethod(int a, double b) {
        return ((char) Math.round(b / a));
    }
    
    @Override
    public void test() {
        System.out.println("test() method from the Test1 object was invoked!");
    }
}
