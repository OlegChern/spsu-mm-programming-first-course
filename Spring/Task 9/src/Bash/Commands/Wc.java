package Bash.Commands;

import java.io.*;
import java.util.List;
import java.util.Scanner;

public class Wc implements Executable {

    private List<String> args;

    Wc(Command command) throws NotEnoughArgumentsException {
        args = command.getArgs();
    }

    @Override
    public String execute() throws FileNotFoundException {
        if (args.isEmpty()) {
            throw new NotEnoughArgumentsException("Please specify path to the file");
        }

        File file = new File(args.get(0));
        Scanner scanner = new Scanner(new BufferedReader(new FileReader(file)));
        StringBuilder fileStr = new StringBuilder("");

        Integer linesNumber = 0;
        Long wordsNumber;
        Long fileSize;

        while (scanner.hasNextLine()) {
            fileStr.append(scanner.nextLine());
            linesNumber++;
        }

        fileSize = file.length();
        wordsNumber = (long) fileStr.toString().split(" ").length;

        return linesNumber.toString() + " " + wordsNumber.toString() + " " + fileSize.toString();
    }

    @Override
    public void addArg(String arg) {
        args.add(arg);
    }
}
