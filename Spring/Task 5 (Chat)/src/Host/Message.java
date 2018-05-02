package Host;

import java.io.Serializable;

/**
 * Superclass of all messages:
 * @see TextMessage
 * @see SystemMessage
 *
 * Amount of subclasses is potentually to expand:
 * For instance, DataMessage, ImageMessage, AudioMessage and so on.
 */
public abstract class Message implements Serializable {
    private static final long serialVersionUID = 100L;
}
