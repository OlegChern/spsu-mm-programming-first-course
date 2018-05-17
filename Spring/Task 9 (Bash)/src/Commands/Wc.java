package Commands;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.atomic.AtomicInteger;

public class Wc extends Command {
    
    protected Wc(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        super(args, inputFile, outputFile, outputFileMode, errorFile);
    }
    
    @Override
    public void run() throws IOException, CommandExecutionFailedException {
        AtomicInteger linesCount = new AtomicInteger();
        AtomicInteger wordsCount = new AtomicInteger();
        AtomicInteger bytesCount = new AtomicInteger();
        
        if (args.length > 1) {
            errorWriter.println("wc must not have more than one argument");
            throw new CommandExecutionFailedException("wc must not have more than one argument");
        }
        
        BufferedReader input = args.length == 0 ? inputReader : new BufferedReader(new FileReader(args[0]));
        
        input.lines().forEach(line -> {
            linesCount.set(linesCount.get() + 1);
            wordsCount.set(wordsCount.get() + (line.equals("") ? 0 : line.trim().split("\\s+").length));
            bytesCount.set(bytesCount.get() + line.length());
        });
        
        outputWriter.println("lines: " + linesCount + " words: " + wordsCount + " bytes: " + bytesCount);
    }
}
