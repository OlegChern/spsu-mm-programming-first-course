package Bash.Commands;

import java.util.List;

public class Exit implements Executable {

    private List<String> args;

    Exit(List<String> args) {
        this.args = args;
    }

    @Override
    public String execute() {
        System.exit(0);
        return "program stopped";
    }

    @Override
    public void addArg(String arg) {
        args.add(arg);
    }
}
