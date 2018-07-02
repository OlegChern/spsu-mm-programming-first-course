import WeakHashTable.*;
import Test.*;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        System.out.println("Please enter time period during which you want to test HashTable");
        int Time = sc.nextInt();
        HashTable<Test, String> table = new HashTable <Test, String>(Time);
        System.out.println("Enter the number of objects you want to add to table");
        int k = sc.nextInt();
        for (int i = 0; i < k; i++) {
            String s = sc.nextLine();
            table.put(new Test(i), s);
            System.out.println("Waiting for value...");
        }
        String s = sc.nextLine();
        table.put(new Test(k), s);

        System.out.println("Initial state:\n" + table + "\n");
        System.gc();
        Thread.sleep(Time / 2);

        System.out.println("What garbage collector has done :\n" + table + "\n");
        Thread.sleep(Time / 2 + 1);
        System.gc();
        Thread.sleep(Time);
        System.out.println("What happened to the table after garbage collector work when time is over:\n" + table + "\n");
    }
}
