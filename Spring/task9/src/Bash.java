import java.util.HashMap;

public class Bash {

    private ClientInterface clientInterface;
    private String directoryName;
    private HashMap <String, String> variables;
    private Commands commands;

    public Bash() {
        clientInterface = new ClientInterface();
        this.variables = new HashMap<>();
        setDirectoryName();
        commands = new Commands(clientInterface, directoryName, this);
    }

    public void setDirectoryName() {
        clientInterface.println("Enter path where you want to work with bash:");
        this.directoryName = clientInterface.getCommand();
    }

    public void run() {
        clientInterface.printWelcomeMSG();
        while (true) {
            String command = clientInterface.getCommand();
            runCommand(command);
        }
    }

    public void runCommand(String command) {
        String[] commands = command.split("\\|");
        String tmp;
        if (commands.length == 1) {
            ClassifyAndDo(commands[0], null);
        } else {
            String[] otherCommands = new String[commands.length - 1];
            System.arraycopy(commands, 1, otherCommands, 0, commands.length - 1);
            ClassifyAndDo(commands[0], otherCommands);
        }
    }

    public void ClassifyAndDo(String command, String[] otherCommands) {
        //System.out.println(command);
        String[] parsedCommand = command.split(" ");
        //System.out.println(parsedCommand[0]);
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
            //System.out.println(parsedCommand[i]);
            String[] tmp = new String[parsedCommand.length - i - 1];
            System.arraycopy(parsedCommand, i + 1, tmp, 0, parsedCommand.length - i - 1);
            switch (parsedCommand[i].charAt(0)) {
                case 'e':
                    if (parsedCommand[i].equals("exit")) {
                        commands.exit();
                    } else if (parsedCommand[i].equals("echo") && parsedCommand.length - i > 1) {
                        //System.out.println( parsedCommand.length - i);
                        //System.out.println(parsedCommand.length - i - 1);
                        commands.echo(tmp, otherCommands);
                    } else {
                        commands.runWithOS(parsedCommand, otherCommands);
                    }
                    break;
                case 'p':
                    if (parsedCommand[i].equals("pwd")) {
                        commands.pwd(otherCommands);
                    } else {
                        commands.runWithOS(parsedCommand, otherCommands);
                    }
                    break;
                case 'c':
                    if (parsedCommand[i].equals("cat") && parsedCommand.length > 1) {
                        commands.cat(tmp, otherCommands);
                    } else {
                        commands.runWithOS(parsedCommand, otherCommands);
                    }
                    break;
                case 'w':
                    if (parsedCommand[i].equals("wc") && parsedCommand.length > 1) {
                        commands.wc(tmp, otherCommands);
                    } else {
                        commands.runWithOS(parsedCommand, otherCommands);
                    }
                    break;
                case '$':
                    //System.out.println(parsedCommand[i].split("=")[0]);
                    if (parsedCommand[i].split("=").length == 2) {
                        variables.put(parsedCommand[i].split("=")[0].substring(1), parsedCommand[i].split("=")[1]);
                    } else {
                        commands.runWithOS(parsedCommand, otherCommands);
                    }
                    break;
                default:
                    commands.runWithOS(parsedCommand, otherCommands);
                    break;
            }
        }
    }
}