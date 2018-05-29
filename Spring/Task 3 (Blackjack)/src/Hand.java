import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Hand implements Copyable<Hand> {
    private List<Card> cards;
    private double bet;
    private int score;
    
    private boolean hasPlayed;
    private boolean hasFouled;
    
    public Hand(double bet, Card card) {
        this.bet = bet;
        cards = new ArrayList<>();
        takeCard(card);
        this.hasPlayed = false;
        this.hasFouled = false;
    }
    
    public Hand(double bet, Card[] cards) {
        this.bet = bet;
        this.cards = new ArrayList<>();
        for (Card card : cards) {
            takeCard(card);
        }
        this.hasPlayed = false;
        this.hasFouled = false;
    }
    
    public Hand(Hand copied) {
        this.bet = copied.bet;
        cards = new ArrayList<>(copied.cards);
        score = copied.score;
        this.hasPlayed = copied.hasPlayed;
        this.hasFouled = copied.hasFouled;
    }
    
    @Override
    public Hand copy() {
        return new Hand(this);
    }
    
    @Override
    public void copyTo(Hand target) {
        target.bet = this.bet;
        target.score = this.score;
        target.cards.clear();
        this.cards.stream().map(Card::copy).forEach(target.cards::add);
    }
    
    public void takeCard(Card card) {
        cards.add(card);
        
        if (card.getValue() == Card.Value.ACE) {
            this.score += (this.score + 11 > 21) ? 1 : 11;
        } else {
            this.score += card.getValue().getScore();
        }
    }
    
    public boolean isSplittable() {
        return cards.size() == 2 && cards.get(0).getValue().getScore() == cards.get(1).getValue().getScore();
    }
    
    public Hand split() {
        if (!isSplittable()) {
            throw new IllegalStateException("Hand can not be split");
        }
        
        score = cards.get(0).getValue().getScore();
        return new Hand(bet, cards.remove(1));
    }
    
    public boolean hasBlackjack() {
        return cards.size() == 2 && score == 21;
    }
    
    public boolean isBust() {
        return score > 21;
    }
    
    public void doubleBet() {
        bet *= 2;
    }
    
    public double getBet() {
        return bet;
    }
    
    public int getScore() {
        return score;
    }
    
    public boolean hasPlayed() {
        return hasPlayed;
    }
    
    public void setHasPlayed(boolean hasPlayed) {
        this.hasPlayed = hasPlayed;
    }
    
    public boolean hasFouled() {
        return hasFouled;
    }
    
    public void setHasFouled(boolean hasFouled) {
        this.hasFouled = hasFouled;
    }
    
    public List<Card> getCards() {
        return cards;
    }
    
    public void discard() {
        bet = 0;
        cards.clear();
        score = 0;
    }
    
    @Override
    public String toString() {
        return "bet: " + bet + ", cards: " + Arrays.toString(cards.toArray()) + ", score: " + score;
    }
}
