import java.io.*;

public class PluginLoader extends ClassLoader {
    private String path;

    public PluginLoader(String path, ClassLoader parent) {
        super(parent);
        this.path = path;
    }

    @Override
    public Class<?> findClass(String className) throws ClassNotFoundException {
        try {
            byte b[] = fetchClassFromFS(path + className + ".class");
            return defineClass(className, b, 0, b.length);
        } catch (IOException ex) {
            return super.findClass(className);
        }
    }

    private byte[] fetchClassFromFS(String path) throws IOException {
        InputStream inputStream = new FileInputStream(new File(path));
        long length = new File(path).length();
        byte[] bytes = new byte[(int)length];
        int offset = 0;
        int numRead = 0;
        while (offset < bytes.length && (numRead = inputStream.read(bytes, offset, bytes.length - offset)) >= 0) {
            offset += numRead;
        }
        if (offset < bytes.length) {
            throw new IOException("Could not completely read file "+ path);
        }
        inputStream.close();
        return bytes;
    }


}