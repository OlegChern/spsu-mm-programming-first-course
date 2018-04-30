public class Main {

    public static void main(String[] args) {
        HashTable<String, Integer> table = new HashTable<>(100);
        System.out.println("Let's test our hash table and add 3 elements there");
        table.AddElement("first", 1);
        table.AddElement("second", 2);
        table.AddElement("third", 3);
        System.out.println("What's the key of second element?");
        System.out.println(table.findByKey("second"));
        System.out.println("And now delete 3rd element");
        table.DeleteElementByKey("third");
        System.out.println("Let's check whether there is still third element in hashtable");
        table.findByKey("third");
    }
}
