package Bash.Commands;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.List;
import java.util.Scanner;

public class Cat implements Executable {

    private List<String> args;

    Cat(List<String> args) throws NotEnoughArgumentsException {
        if (args.isEmpty()) {
            throw new NotEnoughArgumentsException("Please specify path to the file");
        }
        this.args = args;
    }

    @Override
    public String execute() throws FileNotFoundException {
        File file = new File(args.get(0));
        Scanner scanner = new Scanner(new BufferedReader(new FileReader(file)));
        StringBuilder result = new StringBuilder("");

        while(scanner.hasNextLine()) {
            result.append(scanner.nextLine());
            if(scanner.hasNextLine())
                result.append("\n");
        }
        return result.toString();
    }

    @Override
    public void addArg(String arg) {
        args.add(arg);
    }
}
