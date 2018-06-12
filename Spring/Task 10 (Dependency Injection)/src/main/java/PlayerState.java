import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;


public class PlayerState implements Copyable<PlayerState> {
    private List<Hand> hands;
    
    public PlayerState(Hand hand) {
        this.hands = new LinkedList<>();
        this.hands.add(hand);
    }
    
    public PlayerState(PlayerState copied) {
        this.hands = copied.hands.stream().map(Hand::new).collect(Collectors.toList());
    }
    
    @Override
    public PlayerState copy() {
        return new PlayerState(this);
    }
    
    @Override
    public void copyTo(PlayerState target) {
        target.hands.clear();
        this.hands.stream().map(Hand::copy).forEach(target.hands::add);
    }
    
    public List<Hand> getHands() {
        return hands;
    }
}
