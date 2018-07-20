package Commands;

import Bash.*;

public abstract class Command {

    protected ClientInterface clientInterface;
    protected String directoryName;
    protected Bash bash;

    public Command(ClientInterface clientInterface, String directoryName, Bash bash) {
        this.directoryName = directoryName;
        this.clientInterface = clientInterface;
        this.bash = bash;
    }

    public abstract void run(String[] args, String[] commands);
}