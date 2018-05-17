package Commands;

import java.io.File;
import java.io.IOException;

@FunctionalInterface
public interface CommandGenerator {
    Command getCommand(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException;
}
