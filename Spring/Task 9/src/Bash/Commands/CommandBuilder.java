package Bash.Commands;

import java.util.ArrayList;
import java.util.List;

public class CommandBuilder {

    private List<String> args;
    private Executable executor;

    public CommandBuilder(List<String> parsedString) {
        switch (parsedString.get(0)) {
            case "echo": {
                parsedString.remove(0);
                args = parsedString;
                executor = new Echo(args);
                break;
            }
            case "exit": {
                args = new ArrayList<>();
                executor = new Exit(args);
                break;
            }
            case "pwd": {
                args = new ArrayList<>();
                executor = new Pwd(args);
                break;
            }
            case "cat": {
                args = new ArrayList<>();
                if (parsedString.size() > 1) {
                    args.add(parsedString.get(1));
                }
                executor = new Cat(args);
                break;
            }
            case "wc": {
                args = parsedString;
                executor = new Wc(args);
                break;
            }
            default: {
                args = parsedString;
                executor = new SystemCall(args);
                break;
            }
        }
    }

    public void addArg(String arg) {
        executor.addArg(arg);
    }

    public String executeCommand() throws Exception {
        return executor.execute();
    }

    public List<String> getArgs() {
        return args;
    }
}

