import WeekHashMap.WeakHashMap;

public class Main {

    private static final int DELAY = 1500;

    public static void main(String[] args) throws InterruptedException {

        WeakHashMap<TestObject, Integer> map = new WeakHashMap<>(DELAY, 4);

        map.put(new TestObject("TEST STRING OBJECT #1"), 5);
        map.put(new TestObject("TEST STRING OBJECT #2"), 6);
        map.put(new TestObject("TEST STRING OBJECT #3"), 7);
        map.put(new TestObject("TEST STRING OBJECT #4"), 8);

        System.out.println("Before any changes:\n" + map + "\n");

        System.gc();
        Thread.sleep(1000);

        System.out.println("After the start of execution of garbage collector but before the elements' timeout:\n" + map + "\n");

        Thread.sleep(1100);
        System.gc();
        Thread.sleep(2000);

        System.out.println("After the start of garbage collector execution and after the timeout:\n" + map);
    }
}
