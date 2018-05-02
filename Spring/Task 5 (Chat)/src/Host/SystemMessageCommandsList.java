package Host;


/**
 * This class stores all type of system messages:
 * @see SystemMessage
 *
 * This class is potentially to expand. In the circumstances of the current task
 * it stores only {@linkplain #KILL_CONNECTION_MARK}.
 */
class SystemMessageCommandsList {
    
    static final int KILL_CONNECTION_MARK = 1;
    
    private SystemMessageCommandsList() {}
}
