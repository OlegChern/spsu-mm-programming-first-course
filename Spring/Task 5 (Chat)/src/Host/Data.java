package Host;

import java.io.Serializable;

/**
 * Superclass of all data classes:
 * @see HostData
 * @see UserData
 * @see PeersList
 *
 * This class is potentually to expand:
 * For instance, File, which can be shared by peers (e.g. torrent-system) and so on.
 */
public abstract class Data implements Serializable {
    private static final long serialVersionUID = 100L;
}
