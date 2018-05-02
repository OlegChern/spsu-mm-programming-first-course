package Host;


/**
 * Encapsulates user text message.
 * @see MessagesService#run()
 */
public class TextMessage extends Message {
    private String text;
    
    private static final long serialVersionUID = 100L;
    
    public TextMessage(String text) {
        this.text = text;
    }
    
    public String getText() {
        return text;
    }
    
    public void setText(String text) {
        this.text = text;
    }
}
