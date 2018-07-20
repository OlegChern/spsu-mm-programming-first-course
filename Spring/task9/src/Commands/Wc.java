package Commands;

import java.io.*;

import Bash.*;

public class Wc extends Command {

    public Wc(ClientInterface clientInterface, String directoryName, Bash bash) {
        super(clientInterface, directoryName, bash);
    }

    @Override
    public void run(String[] args, String[] commands) {
        String line, result;
        for (int i = 0; i < args.length; i++) {
            int lines = 0, words = 0;
            try {
                File f;
                if (args[i].startsWith(directoryName + "\\")) {
                    args[i] = args[i].substring(directoryName.length() + 1);
                }
                f = new File(directoryName + "\\" + args[i]);
                BufferedReader fin = new BufferedReader(new FileReader(f));
                while ((line = fin.readLine()) != null) {
                    lines++;
                    words += line.split(" ").length;
                }
                result = lines + " lines " + words + " words " + f.length() + " bytes";
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
            } catch (FileNotFoundException e) {
                clientInterface.println("File " + args[i] + " not found!!");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
