import TestInterface.Loadable;

import java.io.IOException;

import java.net.URL;
import java.net.URLClassLoader;
import java.util.jar.JarFile;

public class Main {
    
    public static void main(String[] args) throws IOException {

        if (args.length < 1) {
            System.out.println("Please specify path to the jar archive");
            return;
        }

        String filePath = args[0];
        JarFile archive = new JarFile(filePath);

        URL[] url = new URL[]{new URL("jar:file:" + filePath + "!/")};
        URLClassLoader loader = URLClassLoader.newInstance(url);

        archive.stream()
                .filter(entry -> !entry.isDirectory() && entry.getName().endsWith(".class"))
                .map(entry -> {
                    Class<?> temp = null;
                    try {
                        String name = entry.getName().substring(0, entry.getName().length() - ".class".length()).replace("/", ".");
                        temp = loader.loadClass(name);
                    } catch (ClassNotFoundException ex) {
                        System.err.println(ex.getMessage());
                    }
                    return temp;
                })
                .filter(Loadable.class::isAssignableFrom)
                .forEach(clss -> {
                    try {
                        ((Loadable) clss.newInstance()).load();
                    } catch (InstantiationException | IllegalAccessException ex) {
                        System.err.println(ex.getMessage());
                    }
                });
    }
}
