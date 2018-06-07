package Bash.Commands;

import java.util.ArrayList;
import java.util.List;

public class Command {

    private List<String> args;
    private Executable executor;

    public Command(List<String> parsedString) {
        switch (parsedString.get(0)) {
            case "echo": {
                parsedString.remove(0);
                args = parsedString;
                executor = new Echo(this);
                break;
            }
            case "exit": {
                args = new ArrayList<>();
                executor = new Exit(this);
                break;
            }
            case "pwd": {
                args = new ArrayList<>();
                executor = new Pwd(this);
                break;
            }
            case "cat": {
                args = new ArrayList<>();
                if (parsedString.size() > 1) {
                    args.add(parsedString.get(1));
                }
                executor = new Cat(this);
                break;
            }
            case "wc": {
                args = new ArrayList<>();
                args.add(parsedString.get(1));
                if (parsedString.size() > 1) {
                    args.add(parsedString.get(1));
                }
                executor = new Wc(this);
                break;
            }
            default: {
                args = parsedString;
                executor = new SystemCall(this);
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

