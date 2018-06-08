import java.io.*;

public class Reader {

    private BufferedReader reader;

    Reader(File input) throws FileNotFoundException {
        reader = new BufferedReader(new FileReader(input));
    }

    public String readFile() throws IOException {
        StringBuilder result = new StringBuilder("");
        String currentLine;

        while ((currentLine = reader.readLine()) != null) {
            result.append(currentLine);
        }

        return result.toString();
    }
}
