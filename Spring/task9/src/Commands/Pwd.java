package Commands;

import Bash.Bash;
import Bash.ClientInterface;

import java.io.File;

public class Pwd extends Command {

    public Pwd(ClientInterface clientInterface, String directoryName, Bash bash) {
        super(clientInterface, directoryName, bash);
    }

    @Override
    public void run(String[] args, String[] commands) {
        clientInterface.println("Your directory: " + directoryName);
        File directory = new File(directoryName);
        File[] fList = directory.listFiles();
        if (fList == null) {
            clientInterface.println("No such directory!");
            return;
        }
        if (fList.length == 0) {
            clientInterface.println("No files in this directory!!");
            return;
        }
        if (commands == null) {
            for (File file : fList) {
                clientInterface.println(file.getName());
            }
        } else {
            String[] otherCommands;
            if (commands.length == 1) {
                otherCommands = null;
            } else {
                otherCommands = new String[commands.length - 1];
                System.arraycopy(commands, 1, otherCommands, 0, commands.length - 1);
            }
            for (File file : fList) {
                clientInterface.println(file.getName());
                bash.ClassifyAndDo(commands[0] + " " + file.getName(), otherCommands);
            }
        }
    }
}
