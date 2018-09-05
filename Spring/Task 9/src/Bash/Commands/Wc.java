package Bash.Commands;

import java.io.*;
import java.util.List;
import java.util.Scanner;

public class Wc implements Executable {

    private List<String> args;

    Wc(List<String> args) {
        this.args = args;
    }

    @Override
    public String execute() throws NotEnoughArgumentsException {
        Integer totalLines = 0;
        Long totalWords = (long) 0;
        Long totalSize = (long) 0;
        boolean mark = false;
        for (String currentArg : args) {
            File file = new File(currentArg);
            try (Scanner scanner = new Scanner(new BufferedReader(new FileReader(file)))) {
                StringBuilder fileStr = new StringBuilder("");
                Integer linesNumber = 0;
                while (scanner.hasNextLine()) {
                    fileStr.append(scanner.nextLine());
                    linesNumber++;
                }
                totalSize += file.length();
                totalWords += (long) fileStr.toString().split(" ").length;
                totalLines += linesNumber;
                mark = true;
            } catch (FileNotFoundException e) { }
        }

        if (mark) {
            return totalLines.toString() + " " + totalWords.toString() + " " + totalSize.toString();
        } else {
            throw new NotEnoughArgumentsException("Please specify path to the file!");
        }
    }

    @Override
    public void addArg(String arg) {
        args.addAll(List.of(arg.split("\\s")));
    }
}
