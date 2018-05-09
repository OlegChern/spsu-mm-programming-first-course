import WeakHashMapWithCertainDelay.WeakHashMapWithCertainDelay;

import java.util.Objects;

class TestObject {
    private int i;
    
    public TestObject(int i) {
        this.i = i;
    }
    
    @Override
    public String toString() {
        return "TestObject{" + i + "}";
    }
    
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || getClass() != o.getClass()) {
            return false;
        }
        TestObject that = (TestObject) o;
        return i == that.i;
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(i);
    }
}

public class Main {
    
    private static final int DELAY = 2000;
    
    public static void main(String[] args) throws InterruptedException {
        WeakHashMapWithCertainDelay<TestObject, Integer> map = new WeakHashMapWithCertainDelay<TestObject, Integer>(DELAY);
        map.put(new TestObject(1), 17);
        map.put(new TestObject(2), 29);
        map.put(new TestObject(3), 33);
        
        System.out.println("Initial state:\n" + map + "\n");
        
        // run the garbage collector
        System.gc();
        // sleeps while garbage collector is working
        Thread.sleep(1000);
        
        System.out.println("After the garbage collector execution but before the map storage time expiry:\n" + map + "\n");
        
        // sleeps until the map references become weak
        Thread.sleep(1100);
        // run the garbage collector
        System.gc();
        // sleeps while the garbage collector is working
        Thread.sleep(1000);
    
        System.out.println("After the garbage collector execution and after the map storage time expiry:\n" + map + "\n");
    }
}
