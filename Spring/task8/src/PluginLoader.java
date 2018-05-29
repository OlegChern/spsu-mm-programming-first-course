import TestInterface.Interface;

import java.io.*;
import java.net.URL;
import java.net.URLDecoder;
import java.util.*;

public class PluginLoader extends ClassLoader {

    public static void main(String[] args) throws ClassNotFoundException {

        Scanner sc = new Scanner(System.in);
        System.out.println("Input the path to package where you store classes");
        System.out.println("Example path: C:\\Users\\Admin\\Desktop\\task8\\src\\TestClasses");
        String packagePath = sc.nextLine();
        char[] chArray = packagePath.toCharArray();
        int i = chArray.length - 1;
        while (chArray[i] != '\\')
        { --i; }
        String packageName = new String(chArray, i + 1, (chArray.length - i - 1));
        List<Class> classes = PluginLoader.getClassesFromPackage(packageName);
        for (Class c : classes) {
            try {
                Interface execute = (Interface) c.newInstance();
                execute.test();
            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }

    }


    private static List<Class> getClassesFromPackage(String pckgname) throws ClassNotFoundException {
        ArrayList<File> dir = new ArrayList<>();
        try {
            ClassLoader loader = Thread.currentThread().getContextClassLoader();
            if (loader == null) {
                throw new ClassNotFoundException("Can't get class loader.");
            }
            String path = pckgname.replace('.', '/');
            Enumeration<URL> resources = loader.getResources(path);
            while (resources.hasMoreElements()) {
                dir.add(new File(URLDecoder.decode(resources.nextElement().getPath(), "UTF-8")));
            }
        } catch (NullPointerException x) {
            throw new ClassNotFoundException(pckgname + " does not appear to be a valid package (Null pointer exception)");
        } catch (UnsupportedEncodingException encex) {
            throw new ClassNotFoundException(pckgname + " does not appear to be a valid package (Unsupported encoding)");
        } catch (IOException ioex) {
            throw new ClassNotFoundException("IOException was thrown when trying to get all resources for " + pckgname);
        }

        ArrayList<Class> classes = new ArrayList<>();
        for (File directory : dir) {
            if (directory.exists()) {
                String[] files = directory.list();
                for (String file : files) {
                    if (file.endsWith(".class")) {
                        classes.add(Class.forName(pckgname + '.' + file.substring(0, file.length() - 6)));
                    }
                }
            } else {
                throw new ClassNotFoundException(pckgname + " (" + directory.getPath() + ") does not appear to be a valid package");
            }
        }
        return classes;
    }
}