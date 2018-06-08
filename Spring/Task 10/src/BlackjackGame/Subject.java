package BlackjackGame;

public interface Subject {

    void addObserver(Observer observer);

    void doNotify(GameEvent event);
}
