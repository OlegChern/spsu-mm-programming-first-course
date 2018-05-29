import java.util.Map;
import java.util.stream.Collectors;

public class GameState implements Copyable<GameState> {
    private Map<String, PlayerState> playersStates;
    private Card dealerOpenCard;
    
    public GameState(Map<String, PlayerState> playersStates, Card dealerOpenCard) {
        this.playersStates = playersStates;
        this.dealerOpenCard = dealerOpenCard;
    }
    
    private String copyString(String target) {
        return new StringBuilder(target).toString();
    }
    
    public GameState(GameState gameState) {
        this.playersStates = gameState.playersStates.entrySet().stream().collect(Collectors.toMap(
                (Map.Entry<String, PlayerState> entry) -> copyString(entry.getKey()),
                entry -> entry.getValue().copy()
        ));
        this.dealerOpenCard = gameState.dealerOpenCard.copy();
    }
    
    @Override
    public GameState copy() {
        return new GameState(this);
    }
    
    @Override
    public void copyTo(GameState target) {
        target.playersStates.clear();
        this.playersStates.forEach((key, value) -> target.playersStates.put(copyString(key), value.copy()));
        target.dealerOpenCard = this.dealerOpenCard.copy();
    }
    
    public Map<String, PlayerState> getPlayersStates() {
        return playersStates;
    }
    
    public Card getDealerOpenCard() {
        return dealerOpenCard;
    }
}
