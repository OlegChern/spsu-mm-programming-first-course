package LoadableClass;

import TestInterface.Loadable;

public class ExampleClass1 implements Loadable {

    public void load() {
        int k = 2 + 2;
        System.out.println("I am a loadable class! I sum 2 and 2 and get " + k);
    }
}
