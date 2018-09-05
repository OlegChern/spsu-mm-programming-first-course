package Bash.Commands;

import java.io.File;
import java.io.IOException;
import java.util.List;

public class Pwd implements Executable {

    private List<String> args;

    Pwd(List<String> args) {
        this.args = args;
    }

    @Override
    public String execute() throws IOException {
        StringBuilder result = new StringBuilder("");
        File directory = new File(".");
        result.append("Directory: ");
        result.append(directory.getCanonicalPath());
        result.append("\nContents: ");
        File[] filesList = directory.listFiles();
        for (File file : filesList) {
            if (file.isFile() || file.isDirectory()) {
                result.append(file.getName());
                result.append(" ");
            }
        }

        return result.toString();
    }

    @Override
    public void addArg(String arg) {
        args.add(arg);
    }

}
