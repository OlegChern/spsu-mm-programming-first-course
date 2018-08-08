package Commands;

import Bash.Bash;
import Bash.ClientInterface;

public class Echo extends Command {

    public Echo(ClientInterface clientInterface, String directoryName, Bash bash) {
        super(clientInterface, directoryName, bash);
    }

    @Override
    public void run(String[] args, String[] commands) {
        String result = "";
        if (args.length == 0) {
            String[] tmp = {"echo"};
            bash.getRunWithOS().run(tmp, commands);
        }
        for (String arg : args) {
            result += arg + " ";
        }
        clientInterface.println(result);
        if (commands != null) {
            String[] otherCommands;
            if (commands.length == 1) {
                otherCommands = null;
            } else {
                otherCommands = new String[commands.length - 1];
                System.arraycopy(commands, 1, otherCommands, 0, commands.length - 1);
            }
            bash.ClassifyAndDo(commands[0] + " " + result, otherCommands);
        }
    }
}
