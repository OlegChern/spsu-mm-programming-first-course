package MustImplementTestable;

import TestInterface.Testable;

public class Test2 implements Testable {
    double method(double x) {
        return x * x;
    }
    
    @Override
    public void test() {
        System.out.println("test() method from the Test2 object was invoked!");
    }
}
