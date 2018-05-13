import java.io.File;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String modulePath = sc.nextLine();
        int a = sc.nextInt();
        int b = sc.nextInt();
        PluginLoader loader = new PluginLoader(modulePath, ClassLoader.getSystemClassLoader());
        File dir = new File(modulePath);
        String[] modules = dir.list();
        for (String module: modules) {
            try {
                String moduleName = module.split(".class")[0];
                Class clazz = loader.loadClass(moduleName);
                IntChanger execute = (IntChanger) clazz.newInstance();
                if (execute instanceof IntChanger) {
                    System.out.println(execute.change(a, b));
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
    }
}