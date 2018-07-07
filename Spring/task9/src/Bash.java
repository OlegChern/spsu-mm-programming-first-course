import java.io.*;
import java.util.HashMap;

public class Bash {

    private ClientInterface clientInterface;
    private String directoryName;
    private HashMap<String, String> variables;

    public Bash() {
        clientInterface = new ClientInterface();
        this.variables = new HashMap<>();
        setDirectoryName();
    }

    private void setDirectoryName() {
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

    private void runCommand(String command) {
        String[] commands = command.split("\\|");
        String tmp;
        if (commands.length == 1) {
            clientInterface.println(ClassifyAndDo(commands[0]));
        } else {
            tmp = ClassifyAndDo(commands[0]);
            for (int i = 1; i < commands.length - 1; i++) {
                tmp = ClassifyAndDo(commands[i] + " " + tmp);
            }
            clientInterface.println(ClassifyAndDo(commands[commands.length - 1] + " " + tmp));
        }
    }

    public String ClassifyAndDo(String command) {
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
            switch (parsedCommand[i].charAt(0)) {
                case 'e':
                    if (parsedCommand[i].equals("exit")) {
                        exit();
                    } else if (parsedCommand[i].equals("echo") && parsedCommand.length - i > 1) {
                        String[] tmp = new String[parsedCommand.length - i - 1];
                        System.arraycopy(parsedCommand, i + 1, tmp, 0, parsedCommand.length - i - 1);
                        return echo(tmp);
                    } else {
                        return runWithOS(parsedCommand);
                    }
                case 'p':
                    if (parsedCommand[i].equals("pwd")) {
                        return pwd();
                    } else {
                        return runWithOS(parsedCommand);
                    }
                case 'c':
                    if (parsedCommand[i].equals("cat") && parsedCommand.length > 1) {
                        return cat(parsedCommand[1]);
                    } else {
                        return runWithOS(parsedCommand);
                    }
                case 'w':
                    if (parsedCommand[i].equals("wc") && parsedCommand.length > 1) {
                        return wc(parsedCommand[1]);
                    } else {
                        return runWithOS(parsedCommand);
                    }
                case '$':
                    if (parsedCommand[i].split("=").length == 2) {
                        variables.put(parsedCommand[i].split("=")[0].substring(1), parsedCommand[i].split("=")[1]);
                        return "";
                    } else {
                        return runWithOS(parsedCommand);
                    }
                default:
                    return runWithOS(parsedCommand);
            }
        }
        return "";
    }

    private void exit() {
        clientInterface.printExitMSG();
        System.exit(0);
    }

    private String echo(String[] args) {
        String result = "";
        for (String arg : args) {
            result += arg + " ";
        }
        return result;
    }

    private String pwd() {
        String result = "Your directory: " + directoryName + "\n";
        File directory = new File(directoryName);
        File[] fList = directory.listFiles();
        if (fList == null) {
            return result;
        }
        for (File file : fList) {
            result += file.getName() + "\n";
        }
        return result;
    }

    private String cat(String filename) {
        String line, result = "";
        try {
            //System.out.println(filename);
            File f = new File(directoryName + "\\" + filename);
            BufferedReader fin = new BufferedReader(new FileReader(f));
            while ((line = fin.readLine()) != null) {
                result += line;
            }
            return result;
        } catch (FileNotFoundException e) {
            clientInterface.println("File not found!!");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    private String wc(String filename) {
        String line, result = "";
        int lines = 0, words = 0;
        try {
            File f = new File(directoryName + "\\" + filename);
            BufferedReader fin = new BufferedReader(new FileReader(f));
            while ((line = fin.readLine()) != null) {
                lines++;
                words += line.split(" ").length;
            }
            result = lines + " lines " + words + " words " + f.length() + " bytes";
            return result;
        } catch (FileNotFoundException e) {
            clientInterface.println("File not found!!");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return result;
    }

    private String runWithOS(String[] parsedCommand) {
        Process process;
        String result = "";
        try {
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
                return "";
            }
            return result;
        } catch (IOException e) {
            e.printStackTrace();
            return "";
        }
    }
}
