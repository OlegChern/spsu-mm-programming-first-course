import java.util.Collections;
import java.util.LinkedList;

public class Deck extends LinkedList<Card> {
    public Deck(int numberOfDecks) {
        for (int i = 0; i < numberOfDecks; i++) {
            for (Suit s : Suit.values())
                for (Value v : Value.values()) {
                    Card c = new Card(s, v);
                    this.add(c);
                }

            Collections.shuffle(this);
        }
    }
    public Card Pop()
    {
        Card card = getLast();
        removeLast();
        return card;
    }

}