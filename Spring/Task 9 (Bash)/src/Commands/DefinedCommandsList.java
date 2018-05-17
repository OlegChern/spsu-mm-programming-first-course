package Commands;

public enum DefinedCommandsList {
    CAT("cat", Cat::new),
    ECHO("echo", Echo::new),
    LS("ls", Ls::new),
    PWD("pwd", Pwd::new),
    WC("wc", Wc::new);
    
    private String name;
    private CommandGenerator generator;
    
    DefinedCommandsList(String name, CommandGenerator generator) {
        this.name = name;
        this.generator = generator;
    }
    
    public String getName() {
        return name;
    }
    
    public CommandGenerator getGenerator() {
        return generator;
    }
}
