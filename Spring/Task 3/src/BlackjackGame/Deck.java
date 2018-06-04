package BlackjackGame;

import java.util.ArrayList;
import java.util.Random;

public class Deck {

    private final Integer defaultDeckNumber = 8;
    private final Integer sizeofDeck = 52;

    private ArrayList<Card> cards;
    private Integer currentSize;

    Deck() {

        cards = new ArrayList<>(defaultDeckNumber);
        currentSize = defaultDeckNumber * sizeofDeck;

        for (Suits suit : Suits.values())
            for (Ranks rank : Ranks.values()) {
                for (int i = 0; i < defaultDeckNumber; i++) cards.add(new Card(suit, rank));
            }
    }

    public Integer getCurrentSize() {
        return currentSize;
    }

    public Integer getDefaultSize() {
        return defaultDeckNumber * sizeofDeck;
    }

    public Card Pop() {

        Random rnd = new Random(System.currentTimeMillis());
        Integer temp = rnd.nextInt(currentSize);

        Card result = cards.get(temp);
        cards.remove(temp);
        return result;
    }
}


