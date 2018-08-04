import Bash.Bash;
import Commands.CommandType;

import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {
        ArrayList<CommandType> commandsNames = new ArrayList<>();
        commandsNames.add(CommandType.Exit);
        commandsNames.add(CommandType.Pwd);
        commandsNames.add(CommandType.Wc);
        commandsNames.add(CommandType.Echo);
        commandsNames.add(CommandType.Cat);
        //for activating new command just add it class and name here
        Bash bash = new Bash(commandsNames);
        bash.start();
    }
}

