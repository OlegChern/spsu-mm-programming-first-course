package Host;

import java.net.InetSocketAddress;

/**
 * Stores data about the machine constituent.
 * This class is potentially to expand. In the circumstances of this task it stores only
 * {@linkplain #serverSocketAddress}.
 */
public class HostData extends Data {
    private InetSocketAddress serverSocketAddress;
    
    private static final long serialVersionUID = 100L;
    
    public HostData(InetSocketAddress serverSocketAddress) {
        this.serverSocketAddress = serverSocketAddress;
    }
    
    public InetSocketAddress getServerSocketAddress() {
        return serverSocketAddress;
    }
    
    public void setServerSocketAddress(InetSocketAddress serverSocketAddress) {
        this.serverSocketAddress = serverSocketAddress;
    }
}
