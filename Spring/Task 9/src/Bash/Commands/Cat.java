package Bash.Commands;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.List;
import java.util.Scanner;

public class Cat implements Executable {

    private List<String> args;

    Cat(Command command) throws NotEnoughArgumentsException {
        args = command.getArgs();
    }

    @Override
    public String execute() throws FileNotFoundException {

        if (args.isEmpty()) {
            throw new NotEnoughArgumentsException("Please specify path to the file");
        }

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
