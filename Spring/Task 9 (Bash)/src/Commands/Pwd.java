package Commands;

import java.io.File;
import java.io.IOException;

public class Pwd extends Command {
    
    protected Pwd(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        super(args, inputFile, outputFile, outputFileMode, errorFile);
    }
    
    @Override
    public void run() throws CommandExecutionFailedException {
        if (args.length != 0) {
            errorWriter.println("pwd must not have any arguments");
            throw new CommandExecutionFailedException("pwd must not have any arguments");
        }
        
        outputWriter.println(System.getProperty("user.dir"));
    }
}
