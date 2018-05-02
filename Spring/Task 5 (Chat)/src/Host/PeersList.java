package Host;

import java.net.InetSocketAddress;
import java.util.Collection;


/**
 * Stores data about all connections of the {@linkplain ConnectionsService}.
 * It is used to send new conferee information about all chat conferees so it
 * can connect to them to.
 * @see Host#answer(Connection)
 */
public class PeersList extends Data {
    private InetSocketAddress[] addresses;
    
    private static final long serialVersionUID = 100L;
    
    public PeersList(Collection<Connection> connections) {
        addresses = connections.stream()
                .map(c -> c.getAddresseeHostData().getServerSocketAddress())
                .toArray(InetSocketAddress[]::new);
    }
    
    public InetSocketAddress[] getAddresses() {
        return addresses;
    }
}
