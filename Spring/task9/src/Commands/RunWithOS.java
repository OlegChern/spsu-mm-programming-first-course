package Commands;

import Bash.Bash;
import Bash.ClientInterface;

import java.io.IOException;

public class RunWithOS extends Command {

    public RunWithOS(ClientInterface clientInterface, String directoryName, Bash bash) {
        super(clientInterface, directoryName, bash);
    }

    @Override
    public void run(String[] parsedCommand, String[] commands) {
        Process process;
        String result = "";
        try {
            parsedCommand[0] = "cd " + directoryName + " & " + parsedCommand[0];
            parsedCommand[0] = "cd " + directoryName + " & " + parsedCommand[0];
            process = Runtime.getRuntime().exec(new String[]{"cmd.exe", "/c", String.join(" ", parsedCommand)});
            int i;
            while ((i = process.getInputStream().read()) != -1) {
                System.out.print((char) i);
            }
            while ((i = process.getErrorStream().read()) != -1) {
                clientInterface.print((char) i);
            }
            if (process.exitValue() != 0) {
                return;
            }
            if (commands != null) {
                String[] otherCommands;
                if (commands.length == 1) {
                    otherCommands = null;
                } else {
                    otherCommands = new String[commands.length - 1];
                    System.arraycopy(commands, 1, otherCommands, 0, commands.length - 1);
                }
                clientInterface.println(result);
                bash.ClassifyAndDo(commands[0] + " " + result, otherCommands);
            } else {
                clientInterface.println(result);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
