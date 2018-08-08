package Bash;

import Commands.*;

import java.lang.reflect.Constructor;
import java.util.HashMap;
import java.util.Vector;

public class Bash {

    private ClientInterface clientInterface;
    private String directoryName;
    private HashMap<String, String> variables;
    private HashMap<String, Command> commandsHashmap;
    private Vector<String> commandsNames;
    private RunWithOS runWithOS;


    public Bash(Vector<String> commandsNames) {
        clientInterface = new ClientInterface();
        this.commandsNames = commandsNames;
        this.variables = new HashMap<>();
        setDirectoryName();
        commandsHashmap = commandFactory(clientInterface, directoryName, this);
    }

    private HashMap<String, Command> commandFactory(ClientInterface clientInterface, String directoryName, Bash bash) {
        HashMap<String, Command> commandHashMap = new HashMap<>();
        runWithOS = new RunWithOS(clientInterface, directoryName, this);
        for (String name : commandsNames) {
            try {
                Class<?> clazz = Class.forName("Commands." + name);
                Constructor<?> constructor = clazz.getConstructor(ClientInterface.class, String.class, Bash.class);
                Object instance = constructor.newInstance(clientInterface, directoryName, this);
                commandHashMap.put(name, (Command) instance);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return commandHashMap;
    }

    public void setDirectoryName() {
        clientInterface.println("Enter path where you want to work with bash:");
        this.directoryName = clientInterface.getCommand();
    }

    public void start() {
        clientInterface.printWelcomeMSG();
        while (true) {
            String command = clientInterface.getCommand();
            runCommand(command);
        }
    }

    public RunWithOS getRunWithOS() {
        return runWithOS;
    }

    public void runCommand(String command) {
        String[] commands = command.split("\\|");
        if (commands.length == 1) {
            ClassifyAndDo(commands[0], null);
        } else {
            String[] otherCommands = new String[commands.length - 1];
            System.arraycopy(commands, 1, otherCommands, 0, commands.length - 1);
            ClassifyAndDo(commands[0], otherCommands);
        }
    }

    public void ClassifyAndDo(String command, String[] otherCommands) {
        String[] parsedCommand = command.split(" ");
        int i = 0;
        if (parsedCommand.length > 0) {
            for (int j = 0; j < parsedCommand.length; j++) {
                if (!parsedCommand[j].equals("")) {
                    i = j;
                    break;
                }
            }
            for (int j = i; j < parsedCommand.length; j++) {
                if (!parsedCommand[j].equals("") && parsedCommand[j].charAt(0) == '$' && variables.containsKey(parsedCommand[j].substring(1))) {
                    parsedCommand[j] = variables.get(parsedCommand[j].substring(1));
                }
            }
            String[] tmp = new String[parsedCommand.length - i - 1];
            System.arraycopy(parsedCommand, i + 1, tmp, 0, parsedCommand.length - i - 1);
            for (String name : commandsNames) {
                if (parsedCommand[i].equals(name.toLowerCase())) {
                    commandsHashmap.get(name).run(tmp, otherCommands);
                    return;
                }
            }
            if (parsedCommand[i].charAt(0) == '$' && parsedCommand[i].split("=").length == 2) {
                variables.put(parsedCommand[i].split("=")[0].substring(1), parsedCommand[i].split("=")[1]);
            } else {
                runWithOS.run(parsedCommand, otherCommands);
            }
        }
    }
}