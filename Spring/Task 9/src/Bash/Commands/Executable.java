package Bash.Commands;

public interface Executable {

    String execute() throws Exception;

    void addArg(String arg);
}
