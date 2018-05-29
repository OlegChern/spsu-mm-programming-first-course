import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.ListIterator;


public class ShuffleMachine {
    private List<Card> cards;
    private ListIterator<Card> cardsIterator;
    
    private static final double RESET_WHEN_USED = 0.7;
    
    public ShuffleMachine(int decksCount) {
        if (decksCount <= 0) {
            throw new IllegalArgumentException("Count of decks must be positive, given value: " + decksCount);
        }
    
        cards = new ArrayList<>();
        for (int i = 0; i < decksCount; i++) {
            List<Card> deck = createDeck();
            Collections.shuffle(deck);
            cards.addAll(deck);
        }
        cardsIterator = cards.listIterator();
    }
    
    public Card next() {
        Card result = cardsIterator.next();
        
        if ((double) cardsIterator.nextIndex() / cards.size() > RESET_WHEN_USED) {
            resetCards();
        }
        
        return result;
    }
    
    public Card[] next(int count) {
        if (count <= 0) {
            throw new IllegalArgumentException("count must be positive, given value: " + count);
        }
        
        List<Card> list = new ArrayList<>();
        for (int i = 0; i < count; i++) {
            list.add(next());
        }
        
        return list.toArray(new Card[0]);
    }
    
    private void resetCards() {
        Collections.shuffle(cards);
        cardsIterator = cards.listIterator();
    }
    
    private static List<Card> createDeck() {
        List<Card> deck = new ArrayList<>();
        
        for (Card.Suit suit : Card.Suit.values()) {
            for (Card.Value value : Card.Value.values()) {
                deck.add(new Card(value, suit));
            }
        }
        
        return deck;
    }
}
