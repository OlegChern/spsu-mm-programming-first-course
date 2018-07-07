import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;
import TestInterface.Interface;

public class JarClassLoader {
    private String pathToJar;
    private JarFile jarFile;
    private URLClassLoader classLoader;

    private void setPathToJar(String pathToJar) {
        this.pathToJar = pathToJar;
    }

    private void openJar() {
        try {
            jarFile = new JarFile(pathToJar);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void analyze(JarEntry elem, URLClassLoader classLoader) {
        if (!elem.isDirectory() && elem.getName().endsWith(".class")) {
            try {
                Class<?> newClass = classLoader.loadClass(elem.getName().substring(0, elem.getName().length() - 6).replace("/", "."));
                if (find(newClass.getInterfaces(), Interface.class)) {
                    try {
                        ((Interface)(newClass.newInstance())).test();
                    } catch (InstantiationException | IllegalAccessException e) {
                        e.printStackTrace();
                    }
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
    }

    private boolean find(Class<?>[] interfaces, Class example) {
        for (Class tmp : interfaces) {
            if (tmp.equals(example)) {
                return true;
            }
        }
        return false;
    }

    public void loadFrom(String pathToJar) {
        setPathToJar(pathToJar);
        openJar();
        try {
            URL[] url = new URL[]{new URL("jar:file:" + pathToJar + "!/")};
            classLoader = new URLClassLoader(url);
            Enumeration<JarEntry> list = jarFile.entries();
            while (list.hasMoreElements()) {
                analyze(list.nextElement(), classLoader);
            }
            try {
                jarFile.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }
}
