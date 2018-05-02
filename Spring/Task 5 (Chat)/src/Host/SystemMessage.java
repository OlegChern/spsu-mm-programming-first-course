package Host;


/**
 * Encapsulates message from system constituent of the peer-to-peer net.
 * It stores the only value {@linkplain #commandID} which could be one
 * of the {@linkplain SystemMessageCommandsList}.
 */
public class SystemMessage extends Message {
    private final int commandID;
    
    private static final long serialVersionUID = 100L;
    
    public SystemMessage(int commandID) {
        this.commandID = commandID;
    }
    
    public int getCommandID() {
        return commandID;
    }
}
