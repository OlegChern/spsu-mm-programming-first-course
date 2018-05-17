public enum TokenTypes {
    STREAMS_SWITCH("(>>|>|1>|2>|<){1}"),
    ASSIGN_OPERATOR("={1}"),
    SPACE_SYMBOL("\\s{1}"),
    COMMAND_DELIMITER(";{1}"),
    PIPE("\\|{1}"),
    NAME("");
    
    private String regexp;
    
    private TokenTypes(String regexp) {
        this.regexp = regexp;
    }
    
    public String getRegexp() {
        return this.regexp;
    }
}