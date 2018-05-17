package Commands;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Cat extends Command {
    
    protected Cat(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        super(args, inputFile, outputFile, outputFileMode, errorFile);
    }
    
    @Override
    public void run() throws FileNotFoundException {
        if (args.length == 0) {
            inputReader.lines().forEach(outputWriter::println);
        }
        
        List<FileReader> files = new ArrayList<>();
        for (String arg : args) {
            files.add(new FileReader(arg));
        }
        
        files.stream()
                .map(BufferedReader::new)
                .flatMap(BufferedReader::lines)
                .forEach(outputWriter::println);
    }
}
