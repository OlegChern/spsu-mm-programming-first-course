package Bash;

import Bash.Commands.Command;

import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Parser {

    private Map<String, String> localVariables;

    Parser() {
        localVariables = new HashMap<>();
    }

    List<Command> parse(String inputString) {

        List<Command> commandQueue = new ArrayList<>();

        String[] commands = inputString.split("\\|");

        for (String currentCommand : commands) {
            String tempString = currentCommand.trim();
            ArrayList<String> lexemes = new ArrayList<>(Arrays.asList(tempString.split(" ")));

            searchForInit(lexemes);
            substituteLocalVariables(lexemes);

            if (!lexemes.isEmpty()) {
                commandQueue.add(new Command(lexemes));
            }
        }
        return commandQueue;
    }

    private void searchForInit(ArrayList<String> lexemes) {
        List<String> toBeRemoved = new ArrayList<>();
        Pattern pattern = Pattern.compile("(\\$)(\\w)(\\w?){30}(\\=)(\\w?){30}(\\.?)(\\w?){10}");

        for (String currentLexeme : lexemes) {
            Matcher matcher = pattern.matcher(currentLexeme);
            if (matcher.find()) {

                String toSplit = matcher.group().replace("$", "");
                String temp[] = toSplit.split("=");

                if (temp.length == 1) {
                    localVariables.put(temp[0], "");
                } else {
                    localVariables.put(temp[0], temp[1]);
                }
                toBeRemoved.add(currentLexeme);
            } else {
                break;
            }
        }
        lexemes.removeAll(toBeRemoved);
    }

    private void substituteLocalVariables(ArrayList<String> lexemes) {
        for (int i = 0; i < lexemes.size(); i++) {
            String currentLexeme = lexemes.get(i);
            while (currentLexeme.contains("$")) {

                Pattern pattern = Pattern.compile("(\\$)(\\w)(\\w?){30}");
                Matcher matcher = pattern.matcher(currentLexeme);

                if (matcher.find()) {
                    String temp = matcher.group();
                    temp = temp.replace("$", "");

                    String result = localVariables.getOrDefault(temp, "");
                    result = lexemes.get(i).replace("$" + temp, result);

                    lexemes.set(i, result);
                    currentLexeme = result;
                }
            }
        }
    }


}
