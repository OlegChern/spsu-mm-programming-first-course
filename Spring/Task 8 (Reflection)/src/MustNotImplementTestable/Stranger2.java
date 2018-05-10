package MustNotImplementTestable;

import java.io.Serializable;

public class Stranger2 implements Serializable, Cloneable {
    void someMethod() {
        System.out.println("This text will not be printed");
    }
    
    @Override
    protected Object clone() throws CloneNotSupportedException {
        super.clone();
        return new Stranger2();
    }
}
