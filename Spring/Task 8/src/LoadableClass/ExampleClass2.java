package LoadableClass;

import TestInterface.Loadable;

public class ExampleClass2 implements Loadable {

    public void load() {
        String str1 = "Ja";
        String str2 = "va";
        System.out.println("I am a loadable class too! I concat " + str1 + " and " + str2 + " and get " + str1.concat(str2));
    }
}
