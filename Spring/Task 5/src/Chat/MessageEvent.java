package Chat;

public class MessageEvent {

    private MessageType type;
    private String text;
    private String user;

    MessageEvent(String message, String username, MessageType type) {
        this.text = message;
        this.type = type;
        this.user = username;
    }

    MessageEvent(String message) {
        text = message;
        if (message.startsWith("/")) {
            if (message.equals("/exit")) {
                type = MessageType.Exit;
            } else if (message.startsWith("/help")) {
                type = MessageType.Help;
            } else if (message.startsWith("/connect")) {
                type = MessageType.Connect;
            } else if (message.equals("/list")) {
                type = MessageType.List;
            } else {
                type = MessageType.InvalidCommand;
            }
        } else {
            type = MessageType.SentText;
        }
    }

    public String getUser() {
        return user;
    }

    public String getText() {
        return text;
    }

    public MessageType getType() {
        return type;
    }
}
