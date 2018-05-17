import Commands.Command;
import Commands.CommandExecutionFailedException;
import Commands.SystemCommand;

import java.io.*;
import java.util.*;
import java.util.stream.Stream;

public class StackExecutor {
    
    private Deque<Token> stack;
    
    private List<Command> commands;
    
    private Map<String, String> variables;
    
    public StackExecutor() {
        stack = new ArrayDeque<>();
        commands = new ArrayList<>();
        variables = new HashMap<>();
    }
    
    public void run(Token[] tokens) throws IncorrectSyntaxException, IOException, UnknownVariableException,
            CommandExecutionFailedException, IncorrectSemanticsException {
    
        reset();
        
        // adds command delimiter as last fictive element
        // it guarantees that all elements in stack will be handled
        tokens = Stream.concat(Arrays.stream(tokens), Stream.of(new Token(TokenTypes.COMMAND_DELIMITER, "")))
                .toArray(Token[]::new);
        
        File inputFile = null;
        File outputFile = null;
        boolean outputFileMode = false;
        File errorFile = null;
        
        Iterator<Token> iterator = Arrays.stream(tokens).iterator();
        while (iterator.hasNext()) {
            Token token = iterator.next();
            
            switch (token.getType()) {
                case SPACE_SYMBOL:
                    // spaces are ignored
                    break;
                case STREAMS_SWITCH:
                    stack.add(token);
                    break;
                case ASSIGN_OPERATOR:
                    if (stack.isEmpty() || stack.peekLast().getType() != TokenTypes.NAME) {
                        throw new IncorrectSyntaxException(token + " expected variable name on the left");
                    }
                    stack.add(token);
                    break;
                case NAME:
                    // substitutes variable on its value
                    if (token.getValue().charAt(0) == '$') {
                        String varName = token.getValue().substring(1);
                        if (variables.keySet().contains(varName)) {
                            token.setValue(variables.get(varName));
                        } else {
                            throw new UnknownVariableException("Unknown variable: " + varName);
                        }
                    }
                    
                    if (!stack.isEmpty() && stack.peekLast().getType() == TokenTypes.STREAMS_SWITCH) {
                        Token streamSwitch = stack.pollLast();
                        StreamsSwitches streamsSwitchType = StreamsSwitches.parse(streamSwitch.getValue());
                        switch (streamsSwitchType) {
                            case INPUT:
                                inputFile = new File(token.getValue());
                                break;
                            case OUTPUT:
                                outputFile = new File(token.getValue());
                                outputFileMode = false;
                                break;
                            case OUTPUT_APPEND:
                                outputFile = new File(token.getValue());
                                outputFileMode = true;
                                break;
                            case ERROR:
                                errorFile = new File(token.getValue());
                                break;
                            default:
                                throw new IllegalArgumentException();
                        }
                    } else if (!stack.isEmpty() && stack.peekLast().getType() == TokenTypes.ASSIGN_OPERATOR) {
                        stack.pollLast();
                        Token variableName = stack.pollLast();
                        variables.put(variableName.getValue(), token.getValue());
                    } else {
                        stack.add(token);
                    }
                    break;
                case PIPE:
                case COMMAND_DELIMITER:
                    List<String> args = new ArrayList<>();
                    String commandName;
                    
                    while (!stack.isEmpty()) {
                        Token previousToken = stack.pollLast();
                        
                        switch (previousToken.getType()) {
                            case NAME:
                                args.add(previousToken.getValue());
                                break;
                            case STREAMS_SWITCH:
                                throw new IncorrectSyntaxException(previousToken + " expected file name");
                            case ASSIGN_OPERATOR:
                                throw new IncorrectSyntaxException(previousToken + " expected value");
                            case PIPE:
                                if (args.isEmpty()) {
                                    throw new IncorrectSyntaxException(previousToken + " expected command on the right");
                                }
                                
                                // pipes work only when left command output stream is standard
                                Command previousCommand = commands.get(commands.size() - 1);
                                if (previousCommand.getOutputFile() == null) {
                                    File tmp = File.createTempFile("bash", null);
                                    tmp.deleteOnExit();
                                    previousCommand.setOutputFile(tmp, false);
                                    inputFile = tmp;
                                }
                        }
                    }
                    
                    boolean hasLeftCommand = !args.isEmpty();
                    if (hasLeftCommand) {
                        if (inputFile != null && (inputFile.equals(outputFile) || inputFile.equals(errorFile))) {
                            throw new IncorrectSemanticsException("input and output in the same file: " + inputFile.getName());
                        }
                        
                        Collections.reverse(args);
                        commandName = args.remove(0);
                        Command command = Command.forName(
                                commandName,
                                args.toArray(new String[0]),
                                inputFile,
                                outputFile,
                                outputFileMode,
                                errorFile
                        );
                        
                        if (command == null) {
                            command = new SystemCommand(
                                    commandName, args.toArray(new String[0]), inputFile, outputFile, outputFileMode, errorFile);
                        }
                        commands.add(command);
                    }
                    
                    if (token.getType() == TokenTypes.PIPE && !hasLeftCommand) {
                        throw new IncorrectSyntaxException(token + " expected command on the left");
                    }
    
                    if (token.getType() == TokenTypes.PIPE) {
                        stack.add(token);
                    }
                    
                    inputFile = null;
                    outputFile = null;
                    errorFile = null;
            }
        }
        
        for (Command command : commands) {
            command.run();
            command.closeStreams();
        }
    }
    
    private void reset() {
        stack.clear();
        commands.clear();
    }
}
