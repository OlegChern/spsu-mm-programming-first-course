import IceCreamLib.*;
import Implementations.Cornet;
import Implementations.Eskimo;
import Implementations.IcePop;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {

        List<IceCream> testList = new ArrayList<>();

        testList.add(new Eskimo());
        testList.add(new Cornet());
        testList.add(new IcePop());

        for (IceCream ice : testList) {
            System.out.println(ice.getFullInfo());
            System.out.println("\n");
        }

    }
}
