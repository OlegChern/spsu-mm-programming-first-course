package Host;

// /connectTo 127.0.0.1:4444

import java.io.IOException;
import java.util.Arrays;


/**
 * The main class of the chat. It represents the peer of the peer-to-peer net.
 * Class consists of the
 * 1.) {@linkplain #connectionsService}
 * 2.) {@linkplain #uiService}
 * 3.) {@linkplain #messagesService}.
 *
 * It cares about their instantiation and setting and coordinates their work
 * during the user session.
 *
 * Host implements greeting and farewell protocols for the {@linkplain #connectionsService}:
 * @see #greet(Connection)
 * @see #answer(Connection)
 * @see #onClosure(Connection)
 *
 * Certainly, Host stores all data about this peer:
 * @see #hostData
 * @see #userData
 */
public class Host {
    private HostData hostData;
    private UserData userData;
    
    private ConnectionsService connectionsService;
    private UIService uiService;
    private MessagesService messagesService;
    
    public Host(HostData hostData, UserData userData) throws IOException {
        this.hostData = hostData;
        this.userData = userData;
        
        this.connectionsService = new ConnectionsService(hostData.getServerSocketAddress().getPort());
        this.connectionsService.setPerformGreeting(this::greet);
        this.connectionsService.setAcceptGreeting(this::answer);
        this.connectionsService.setOnConnectionServiceClosure(this::onClosure);
        
        this.uiService = new UIService(connectionsService, System.in, System.out);
        this.uiService.setOnTermination(this::stop);
        
        this.messagesService = new MessagesService(connectionsService, uiService);
        this.uiService.setMessagesService(messagesService);
    }
    
    public void start() {
        this.connectionsService.start();
        this.uiService.start();
        this.messagesService.start();
        
        this.uiService.printMessageFromProgram("Waiting for connections...");
    }
    
    public void stop() {
        this.connectionsService.stop();
        this.uiService.stop();
        this.messagesService.stop();
    }
    
    //region GreetingProtocol
    
    /**
     * This function is called when host is connecting to the new peer.
     * It represents the greeting of the Greeting Protocol:
     * 1.) Firstly, It sends data about itself.
     * 2.) Then, it receives data about connecting peer and the list of its connections
     * to connect with all of them to unite in the joint informational space.
     * @see PeersList
     *
     * @param conferee Peer to whom connection is setting
     * @return {@code true} if greeting protocol was successfully performed and {@code false} otherwise.
     */
    private boolean greet(Connection conferee) {
        try {
            if (!conferee.isWritable()) {
                return false;
            }
            conferee.send(hostData);
            conferee.send(userData);
            
            if (!conferee.isReadable()) {
                return false;
            }
            Object confereeHostData = conferee.receive();
            if (!(confereeHostData instanceof HostData)) {
                return false;
            }
            Object confereeUserData = conferee.receive();
            if (!(confereeUserData instanceof UserData)) {
                return false;
            }
            Object peersList = conferee.receive();
            if (!(peersList instanceof PeersList)) {
                return false;
            }
            
            conferee.setAddresseeHostData((HostData) confereeHostData);
            conferee.setAddresseeUserData((UserData) confereeUserData);
            
            connectionsService.getConnections().add(conferee);
            
            Arrays.stream(((PeersList) peersList).getAddresses())
                    .filter(socketAddress -> !connectionsService.isConnectedWith(socketAddress))
                    .forEach(uiService::connectWithUIFeedbackTo);
            return true;
            
        } catch (IOException | ClassNotFoundException ignored) {
            
        }
        
        return false;
    }
    
    /**
     * This function is called when this host is receiving incoming connection from the
     * another peer.
     * It represents the acceptance of the Greeting Protocol:
     * 1.) Firstly, it receives a data about the connecting peer.
     * 2.) Secondly, it sends data about itself and also all its connections via {@linkplain PeersList}
     * so the new peer will be able to connect with each of them and eventually unite with them in the
     * joint informational space.
     *
     * @param newSubscriber Peer who is setting connections with this host
     * @return {@code true} if greeting protocol was successfully performed and {@code false} otherwise.
     */
    private boolean answer(Connection newSubscriber) {
        try {
            if (!newSubscriber.isReadable()) {
                return false;
            }
            Object newSubscriberHostData = newSubscriber.receive();
            if (!(newSubscriberHostData instanceof HostData)) {
                return false;
            }
            Object newSubscriberUserData = newSubscriber.receive();
            if (!(newSubscriberUserData instanceof UserData)) {
                return false;
            }
            
            if (!newSubscriber.isWritable()) {
                return false;
            }
            
            newSubscriber.send(hostData);
            newSubscriber.send(userData);
            newSubscriber.send(new PeersList(connectionsService.getConnections()));
            
            newSubscriber.setAddresseeHostData((HostData) newSubscriberHostData);
            newSubscriber.setAddresseeUserData((UserData) newSubscriberUserData);
            
            uiService.printMessageFromProgram(newSubscriber.getAddresseeUserData().getName() +
                    " [" + newSubscriber.getAddresseeHostData().getServerSocketAddress() + "] connected to the chat");
            
            return true;
            
        } catch (IOException | ClassNotFoundException ignored) {
            
        }
        
        return false;
    }
    //endregion
    
    //region DisconnectingProtocol
    void onClosure(Connection breakingConnection) {
        if (breakingConnection.isWritable()) {
            try {
                breakingConnection.send(new SystemMessage(SystemMessageCommandsList.KILL_CONNECTION_MARK));
            } catch (IOException ignore) {
            
            }
        }
    }
    //endregion
}

