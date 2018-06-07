package Bash.Commands;

class NotEnoughArgumentsException extends RuntimeException {

    NotEnoughArgumentsException(String message) {
        super(message);
    }
}
