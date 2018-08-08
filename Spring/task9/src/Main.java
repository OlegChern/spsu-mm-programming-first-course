import Bash.Bash;

import java.util.Vector;

public class Main {

    public static void main(String[] args) {
        Vector<String> commandsNames = new Vector<>();
        commandsNames.add("Exit");
        commandsNames.add("Pwd");
        commandsNames.add("Wc");
        commandsNames.add("Echo");
        commandsNames.add("Cat");
        //for activating new command just add it class and name here
        Bash bash = new Bash(commandsNames);
        bash.start();
    }
}
