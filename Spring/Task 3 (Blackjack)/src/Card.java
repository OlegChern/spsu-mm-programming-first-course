public class Card implements Copyable<Card> {
    private Value value;
    private Suit suit;
    
    public Card(Value value, Suit suit) {
        this.value = value;
        this.suit = suit;
    }
    
    public Card(Card copied) {
        this.value = copied.value;
        this.suit = copied.suit;
    }
    
    @Override
    public Card copy() {
        return new Card(this);
    }
    
    @Override
    public void copyTo(Card target) {
        target.value = this.value;
        target.suit = this.suit;
    }
    
    public Value getValue() {
        return value;
    }
    
    public Suit getSuit() {
        return suit;
    }
    
    public enum Value {
        TWO(2),
        THREE(3),
        FOUR(4),
        FIVE(5),
        SIX(6),
        SEVEN(7),
        EIGHT(8),
        NINE(9),
        TEN(10),
        JACK(10),
        QUEEN(10),
        KING(10),
        ACE(11);
        
        private final int score;
        
        Value(int score) {
            this.score = score;
        }
        
        public int getScore() {
            return score;
        }
    }
    
    public enum Suit {
        HEARTS,
        DIAMONDS,
        CLUBS,
        SPADES
    }
    
    @Override
    public String toString() {
        return "{" + value + "," + suit + "}";
    }
}
