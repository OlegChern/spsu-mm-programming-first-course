package Commands;

import java.io.File;
import java.io.IOException;


public class SystemCommand extends Command {
    
    private String commandName;
    
    public SystemCommand(String commandName, String args[], File inputFile, File outputFile, boolean outputFileMode, File errorFile)
            throws IOException {
        
        super(args, inputFile, outputFile, outputFileMode, errorFile);
        this.commandName = commandName;
    }
    
    @Override
    public void run() throws CommandExecutionFailedException, IOException {
        boolean isWindows = System.getProperty("os.name").toLowerCase().startsWith("windows");
        ProcessBuilder builder = new ProcessBuilder();
        
        String[] command = new String[3];
        if (isWindows) {
            command[0] = "cmd.exe";
            command[1] = "/c";
        } else {
            command[0] = "sh";
            command[1] = "-c";
        }
        
        command[2] = commandName + " " + String.join(" ", args);
        
        builder.command(command);
        builder.inheritIO();
        if (inputFile != null) {
            builder.redirectInput(inputFile);
        }
        if (outputFile != null) {
            builder.redirectOutput(
                    outputFileMode ? ProcessBuilder.Redirect.appendTo(outputFile) : ProcessBuilder.Redirect.to(outputFile));
        }
        if (errorFile != null) {
            builder.redirectError(errorFile);
        }
        
        Process process = builder.start();
        
        try {
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                errorWriter.println("Shell returned non-null code: ");
                throw new CommandExecutionFailedException("Shell returned non-null code " + exitCode);
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
