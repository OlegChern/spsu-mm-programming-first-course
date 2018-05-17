package Commands;

import java.io.File;
import java.io.IOException;
import java.util.Arrays;

public class Echo extends Command {
    
    protected Echo(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        super(args, inputFile, outputFile, outputFileMode, errorFile);
    }
    
    @Override
    public void run() {
        String result = Arrays.toString(args);
        result = result.substring(1, result.length() - 1).replace(", ", "\n");
        outputWriter.println(result);
    }
}
