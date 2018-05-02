package Host;

/**
 * Throws when received message type does not accord required or it is unknown.
 * @see MessagesService#run()
 */
class InappropriateMessageTypeException extends RuntimeException {
    InappropriateMessageTypeException() {
    }
    
    InappropriateMessageTypeException(String message) {
        super(message);
    }
}
