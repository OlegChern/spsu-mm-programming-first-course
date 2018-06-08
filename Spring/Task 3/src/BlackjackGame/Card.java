package BlackjackGame;

public class Card {

    private Suits suit;
    private Ranks rank;
    private Integer value;

    Card(Suits suit, Ranks rank) {

        this.rank = rank;
        this.suit = suit;
        this.value = rank.getValue();

    }

    public Ranks getRank() {
        return this.rank;
    }

    public Integer getValue() {
        return this.value;
    }
}
