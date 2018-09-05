package Bash.Commands;

import java.io.*;
import java.util.List;
import java.util.concurrent.Executors;
import java.util.function.Consumer;

import static java.lang.Thread.sleep;

public class SystemCall implements Executable {

    private List<String> args;
    private boolean isWindows;
    private ProcessBuilder builder;
    private ProcessReader result;

    SystemCall(List<String> args) {
        this.args = args;
        isWindows = System.getProperty("os.name").toLowerCase().startsWith("windows");
        builder = new ProcessBuilder();
        result = new ProcessReader();
    }

    @Override
    public String execute() throws IOException, InterruptedException, ExecutionFailedException {

        String[] input = new String[3];
        if (isWindows) {
            input[0] = "cmd.exe";
            input[1] = "/c";
        } else {
            input[0] = "sh";
            input[1] = "-c";
        }

        input[2] = String.join(" ", args);
        builder.command(input);

        Process process = builder.start();

        StreamGobbler streamGobbler = new StreamGobbler(process.getInputStream(), result::append);
        Executors.newSingleThreadExecutor().submit(streamGobbler);

        sleep(10);
        int exitCode = process.waitFor();
        if (exitCode != 0) {
            throw new ExecutionFailedException("System return non-zero code " + exitCode);
        }

        return result.getString().toString();
    }

    @Override
    public void addArg(String arg) {
        args.add(arg);
    }

    private class ProcessReader {
        private StringBuilder string;

        ProcessReader() {
            string = new StringBuilder("");
        }

        void append(String str) {
            string.append(str);
            string.append(" ");
        }

        public StringBuilder getString() {
            return string;
        }
    }

    private class StreamGobbler implements Runnable {
        private InputStream inputStream;
        private Consumer<String> consumer;

        StreamGobbler(InputStream inputStream, Consumer<String> consumer) {
            this.inputStream = inputStream;
            this.consumer = consumer;
        }

        @Override
        public void run() {
            new BufferedReader(new InputStreamReader(inputStream)).lines()
                    .forEach(consumer);
        }
    }
}
