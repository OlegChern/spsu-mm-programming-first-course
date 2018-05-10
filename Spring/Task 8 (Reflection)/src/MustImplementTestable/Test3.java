package MustImplementTestable;

import TestInterface.Testable;

public class Test3 implements Testable, Comparable<Test3> {
    @Override
    public void test() {
        System.out.println("test() method from the Test3 object was invoked!");
    }
    
    @Override
    public int compareTo(Test3 o) {
        return (int) (Math.random() * 100);
    }
}
