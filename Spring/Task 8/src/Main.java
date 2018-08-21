import TestInterface.Loadable;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) throws IOException {

        if (args.length < 1) {
            System.out.println("Please specify path to the jar archive");
            return;
        }

        String path = args[0];
        Path baseDir = Paths.get(path);

        if (!baseDir.toFile().isDirectory()) {
            throw new IOException("Path is specified to a file, not a directory");
        }

        URL[] url = {baseDir.toUri().toURL()};
        URLClassLoader loader = URLClassLoader.newInstance(url);

        List<Loadable> testList = new ArrayList<>();

        Files.walkFileTree(baseDir, new SimpleFileVisitor<Path>() {

            @Override
            public FileVisitResult visitFile(Path file, BasicFileAttributes attributes) {
                if (!file.toFile().isDirectory() && file.toString().endsWith(".class")) {
                    try {
                        String name = file.toString().substring(baseDir.toString().length() + 1, file.toString().length() - 6).replace(File.separator, ".");
                        Class<?> result = loader.loadClass(name);
                        if (Loadable.class.isAssignableFrom(result)) {
                            testList.add((Loadable) result.getDeclaredConstructor().newInstance());
                        }
                    } catch (ClassNotFoundException | IllegalAccessException | InstantiationException | NoSuchMethodException | InvocationTargetException e) {
                        e.printStackTrace();
                        System.exit(1);
                    }
                }
                return FileVisitResult.CONTINUE;
            }
        });

        for (Loadable test : testList) {
            test.load();
        }

    }
}

