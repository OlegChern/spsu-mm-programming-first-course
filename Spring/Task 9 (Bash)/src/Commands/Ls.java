package Commands;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Date;


public class Ls extends Command {
    
    protected Ls(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        super(args, inputFile, outputFile, outputFileMode, errorFile);
    }
    
    public void run() throws IOException, CommandExecutionFailedException {
        if (args.length != 0) {
            errorWriter.println("ls must not have any arguments");
            throw new CommandExecutionFailedException("ls must not have any arguments");
        } else {
            Files.walk(Paths.get(System.getProperty("user.dir")))
                    .map(Path::toFile)
                    .forEach((file) -> outputWriter.println(
                            String.format("%-40s %-8d %tc", file.getName(), file.length(), new Date(file.lastModified()))));
        }
    }
}
