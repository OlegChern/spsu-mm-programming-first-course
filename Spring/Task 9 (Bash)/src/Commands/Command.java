package Commands;

import java.io.*;


public abstract class Command {
    protected String[] args;
    
    protected static final InputStream standardInputStream = System.in;
    protected static final OutputStream standardOutputStream = System.out;
    protected static final OutputStream standardErrorStream = System.err;
    
    protected File inputFile;
    protected File outputFile;
    protected boolean outputFileMode;
    protected File errorFile;
    
    protected BufferedReader inputReader;
    protected PrintWriter outputWriter;
    protected PrintWriter errorWriter;
    
    protected Command(String[] args, File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        this.args = args;
        this.setInputFile(inputFile);
        this.setOutputFile(outputFile, outputFileMode);
        this.outputFileMode = outputFileMode;
        this.setErrorFile(errorFile);
    }
    
    public static Command forName(String name, String[] args,
                                  File inputFile, File outputFile, boolean outputFileMode, File errorFile) throws IOException {
        
        DefinedCommandsList[] values = DefinedCommandsList.values();
        
        for (DefinedCommandsList definedCommand : values) {
            if (definedCommand.getName().equals(name)) {
                return definedCommand.getGenerator().getCommand(args, inputFile, outputFile, outputFileMode, errorFile);
            }
        }
        
        return null;
    }
    
    public abstract void run() throws CommandExecutionFailedException, IOException;
    
    public String[] getArgs() {
        return this.args;
    }
    
    public void setArgs(String[] args) {
        this.args = args;
    }
    
    public File getInputFile() {
        return this.inputFile;
    }
    
    public void setInputFile(File inputFile) throws FileNotFoundException {
        this.inputFile = inputFile;
        this.inputReader = new BufferedReader(
                inputFile == null ?
                        new InputStreamReader(standardInputStream) :
                        new FileReader(inputFile)
        );
    }
    
    public File getOutputFile() {
        return this.outputFile;
    }
    
    public void setOutputFile(File outputFile, boolean outputFileMode) throws IOException {
        this.outputFile = outputFile;
        this.outputWriter = new PrintWriter(
                outputFile == null ?
                        new OutputStreamWriter(standardOutputStream) :
                        new FileWriter(outputFile, outputFileMode),
                true
        );
    }
    
    public File getErrorFile() {
        return this.errorFile;
    }
    
    public void setErrorFile(File errorFile) throws IOException {
        this.errorFile = errorFile;
        this.errorWriter = new PrintWriter(
                errorFile == null ?
                        new OutputStreamWriter(standardErrorStream) :
                        new FileWriter(errorFile),
                true
        );
    }
    
    public void closeStreams() throws IOException {
        if (this.inputFile != null) {
            this.inputReader.close();
        }
        
        if (this.outputFile != null) {
            this.outputWriter.close();
        }
        
        if (this.errorFile != null) {
            this.errorWriter.close();
        }
    }
}
