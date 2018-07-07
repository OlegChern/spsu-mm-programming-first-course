import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        JarClassLoader loader = new JarClassLoader();
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter path for jar file");
        String path = sc.nextLine();
        loader.loadFrom(path);
    }
}
