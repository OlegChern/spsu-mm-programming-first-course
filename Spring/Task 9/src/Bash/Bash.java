package Bash;

import Bash.Commands.Command;

import java.util.List;

public class Bash {

    private UserInterface UI;
    private Parser parser;

    public Bash() {
        UI = new UserInterface();
        parser = new Parser();
    }

    public void run() {
        while (true) {
            try {
                String inputCommand = UI.getLine();
                List<Command> commandList = parser.parse(inputCommand);
                String result = interpretCommand(commandList);
                UI.printResult(result);
            } catch (Exception ex) {
                UI.printError(ex);
            }
        }
    }

    private String interpretCommand(List<Command> commandList) throws Exception {

        String result = "";
        for (Command currentCommand : commandList) {
            if (!result.equals("")) {
                currentCommand.addArg(result);
            }
            result = currentCommand.executeCommand();
        }
        return result;
    }
}

