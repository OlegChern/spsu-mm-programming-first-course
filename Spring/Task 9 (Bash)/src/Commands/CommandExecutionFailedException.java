package Commands;

public class CommandExecutionFailedException extends Exception {
    public CommandExecutionFailedException() {
    }
    
    public CommandExecutionFailedException(String message) {
        super(message);
    }
}
