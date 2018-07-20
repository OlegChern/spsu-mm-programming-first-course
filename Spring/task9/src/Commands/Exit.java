package Commands;

import Bash.Bash;
import Bash.ClientInterface;

public class Exit extends Command {

    public Exit(ClientInterface clientInterface, String directoryName, Bash bash) {
        super(clientInterface, directoryName, bash);
    }

    @Override
    public void run(String[] args, String[] commands) {
        clientInterface.printExitMSG();
        System.exit(0);
    }
}
