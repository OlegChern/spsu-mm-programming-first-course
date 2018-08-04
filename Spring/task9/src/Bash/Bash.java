package Bash;

import Commands.*;

import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.HashMap;

public class Bash {

    private ClientInterface clientInterface;
    private String directoryName;
    private HashMap<String, String> variables;
    private HashMap<CommandType, Command> commandsHashmap;
    private ArrayList<CommandType> commandsNames;
    private RunWithOS runWithOS;

    public Bash(ArrayList<CommandType> commandsNames) {
        clientInterface = new ClientInterface();
        this.commandsNames = commandsNames;
        this.variables = new HashMap<>();
        setDirectoryName();
        commandFactory(clientInterface, directoryName, this);
    }

    private void commandFactory(ClientInterface clientInterface, String directoryName, Bash bash) {
        commandsHashmap = new HashMap<>();
        runWithOS = new RunWithOS(clientInterface, directoryName, this);
        commandsNames.forEach(name -> {
            try {
                Class<?> clazz = Class.forName("Commands." + name);
                Constructor<?> constructor = clazz.getConstructor(ClientInterface.class, String.class, Bash.class);
                Object instance = constructor.newInstance(clientInterface, directoryName, this);
                commandsHashmap.put(name, (Command) instance);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
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
            switch (parsedCommand[i].charAt(0)) {
                case 'e':
                    if (parsedCommand[i].equals("exit")) {
                        commandsHashmap.get(CommandType.Exit).run(tmp, otherCommands);
                    } else if (parsedCommand[i].equals("echo") && parsedCommand.length - i > 1) {
                        commandsHashmap.get(CommandType.Echo).run(tmp, otherCommands);
                    } else {
                        runWithOS.run(parsedCommand, otherCommands);
                    }
                    break;
                case 'p':
                    if (parsedCommand[i].equals("pwd")) {
                        commandsHashmap.get(CommandType.Pwd).run(tmp, otherCommands);
                    } else {
                        runWithOS.run(parsedCommand, otherCommands);
                    }
                    break;
                case 'c':
                    if (parsedCommand[i].equals("cat") && parsedCommand.length > 1) {
                        commandsHashmap.get(CommandType.Cat).run(tmp, otherCommands);
                    } else {
                        runWithOS.run(parsedCommand, otherCommands);
                    }
                    break;
                case 'w':
                    if (parsedCommand[i].equals("wc") && parsedCommand.length > 1) {
                        commandsHashmap.get(CommandType.Wc).run(tmp, otherCommands);
                    } else {
                        runWithOS.run(parsedCommand, otherCommands);
                    }
                    break;
                case '$':
                    if (parsedCommand[i].split("=").length == 2) {
                        variables.put(parsedCommand[i].split("=")[0].substring(1), parsedCommand[i].split("=")[1]);
                    } else {
                        runWithOS.run(parsedCommand, otherCommands);
                    }
                    break;
                default:
                    runWithOS.run(parsedCommand, otherCommands);
                    break;
            }
        }
    }
}
