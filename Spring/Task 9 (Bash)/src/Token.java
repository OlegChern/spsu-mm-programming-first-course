public class Token {
    private TokenTypes type;
    private String value;
    
    public Token(TokenTypes type, String value) {
        this.type = type;
        this.value = value;
    }
    
    public TokenTypes getType() {
        return this.type;
    }
    
    public String getValue() {
        return this.value;
    }
    
    public void setType(TokenTypes type) {
        this.type = type;
    }
    
    public void setValue(String value) {
        this.value = value;
    }
    
    public String toString() {
        return type.toString() + " \"" + value + "\"";
    }
}
