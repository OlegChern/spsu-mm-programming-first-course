package BlackjackGame;

public class GameEvent {

    private Player eventSource;
    private EventType type;

    GameEvent(Player eventSource, EventType type) {
        this.eventSource = eventSource;
        this.type = type;
    }

    public Player getEventSource() {
        return eventSource;
    }

    public EventType getType() {
        return type;
    }

}
