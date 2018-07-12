import java.awt.*;
import java.io.*;

public class Commands {

    private ClientInterface clientInterface;
    private String directoryName;
    private Bash bash;

    public Commands(ClientInterface clientInterface, String directoryName, Bash bash) {
        this.directoryName = directoryName;
        this.clientInterface = clientInterface;
        this.bash = bash;
    }

    public void setDirectoryName(String directoryName) {
        this.directoryName = directoryName;
    }

    public void exit() {
        clientInterface.printExitMSG();
        System.exit(0);
    }

    public void echo(String[] args, String[] commands) {
        String result = "";
        //System.out.println(args.length);
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

    public void pwd(String[] commands) {
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

    public void cat(String[] args, String[] commands) {
        String line, result;
        for (int i = 0; i < args.length; i++) {
            try {
                File f = new File(directoryName + "\\" + args[i]);
                BufferedReader fin = new BufferedReader(new FileReader(f));
                clientInterface.println("File " + args[i] + " contains these symbols:");
                while ((line = fin.readLine()) != null) {
                    result = line;
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
                }
                clientInterface.println("End of file " + args[i] + "!");
            } catch (FileNotFoundException e) {
                clientInterface.println("File " + args[i] + " not found!!");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void wc (String[] args, String[] commands) {
        String line, result;
        for (int i = 0; i < args.length; i++) {
            int lines = 0, words = 0;
            try {
                File f = new File(directoryName + "\\" + args[i]);
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

    public void runWithOS(String[] parsedCommand, String[] commands) {
        Process process;
        String result = "";
        try {
            parsedCommand[0] = "cd " + directoryName + " & " + parsedCommand[0];
            //System.out.println(String.join(" ", parsedCommand));
            process = Runtime.getRuntime().exec(new String[]{"cmd.exe", "/c", String.join(" ", parsedCommand)});
            int i;
            while((i = process.getInputStream().read()) != -1) {
                System.out.print((char)i);
            }
            while((i = process.getErrorStream().read()) != -1) {
                clientInterface.print((char)i);
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
