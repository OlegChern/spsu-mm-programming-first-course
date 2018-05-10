import TestInterface.Testable;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.jar.JarFile;

public class Main {
    
    private static void fatal(Exception e) {
        e.printStackTrace();
        System.exit(1);
    }
    
    private static void fatal(String s) {
        System.err.println(s);
        System.exit(1);
    }
    
    public static void main(String[] args) {
        
        if (args.length < 1) {
            System.out.println("Specify path to the jar file");
            return;
        }
        
        JarFile library = null;
        String pathToJar = args[0];
        
        try {
            library = new JarFile(pathToJar);
        } catch (FileNotFoundException ignored) {
            fatal("Error: file was not found");
        } catch (IOException e) {
            fatal(e);
        }
        
        URL[] url = new URL[0];
        try {
            url = new URL[]{new URL("jar:file:" + pathToJar + "!/")};
        } catch (MalformedURLException e) {
            fatal(e);
        }
        final URLClassLoader classLoader = URLClassLoader.newInstance(url);
        
        library.stream()
                .filter(entry -> !entry.isDirectory() && entry.getName().endsWith(".class"))
                .map(entry -> {
                    Class<?> result = null;
                    try {
                        String loadName = entry.getName().substring(0, entry.getName().length() - 6).replace("/", ".");
                        result = classLoader.loadClass(loadName);
                    } catch (ClassNotFoundException e) {
                        fatal(e);
                    }
                    return result;
                })
                .filter(Testable.class::isAssignableFrom)
                .forEach(c -> {
                    try {
                        ((Testable) c.newInstance()).test();
                    } catch (InstantiationException | IllegalAccessException e) {
                        fatal(e);
                    }
                });
    }
}
