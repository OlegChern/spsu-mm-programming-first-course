package WeakHashMapWithCertainDelay;

public class NotActualStateException extends RuntimeException {
    public NotActualStateException() {
        super();
    }
    
    public NotActualStateException(String message) {
        super(message);
    }
}
