public enum StreamsSwitches {
    INPUT("^<$"),
    OUTPUT("^>|1>$"),
    OUTPUT_APPEND("^>>$"),
    ERROR("^2>$");
    
    private String view;
    
    private StreamsSwitches(String view) {
        this.view = view;
    }
    
    public static StreamsSwitches parse(String operator) {
        if (operator == null) {
            return null;
        } else {
            StreamsSwitches[] streamsSwitches = values();
    
            for (StreamsSwitches streamsSwitch : streamsSwitches) {
                if (operator.matches(streamsSwitch.view)) {
                    return streamsSwitch;
                }
            }
            
            return null;
        }
    }
}
