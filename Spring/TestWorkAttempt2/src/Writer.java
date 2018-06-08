import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Writer {

    private BufferedWriter writer;

    Writer(File output) throws IOException {
        writer = new BufferedWriter(new FileWriter(output));
    }

    public void writeFile(String data) throws IOException {
        writer.write(data);
    }
}
