package Bash.Commands;

import java.util.List;

public class Echo implements Executable {

    private List<String> args;

    Echo(Command command) {
        args = command.getArgs();
    }

    @Override
    public String execute() {
        StringBuilder result = new StringBuilder("");
        for (String currentArg: args) {
            result.append(currentArg);
            result.append(" ");
        }
        return result.toString().trim();
    }

    @Override
    public void addArg(String arg) {
        args.add(arg);
    }
}
