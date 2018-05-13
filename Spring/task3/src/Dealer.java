import java.util.LinkedList;

public class Dealer extends LinkedList<Card>
{

    public Card firstCard;

    public Card getFirstCard() {
        return firstCard;
    }

    public int score;

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        score = score;
    }

    public Dealer()
    {
        score = 0;
    }

    private void AddCard(Deck deck)
    {
        Card card = deck.Pop();
        this.add(card);
        score += card.getScore();
    }

    private void AddFirstCard(Deck decks)
    {
        Card card = decks.Pop();
        this.add(card);
        score += card.getScore();
        firstCard = card;
    }

    public void GiveCard(Player player, Deck decks)
    {
        Card card = decks.Pop();
        player.AddCard(card);
    }

    public void Dealing(LinkedList<Player> players, Deck decks)
    {
        for(int i = 0; i < players.size(); i++)
        {
            GiveCard(players.get(i), decks);
        }
        AddFirstCard(decks);

        for (int i = 0; i < players.size(); i++)
        {
            GiveCard(players.get(i), decks);
        }
        AddCard(decks);
    }

    public void PrintInfo()
    {
        System.out.println("Dealer " + this.size() + " cards ");
        for (int i = 0; i < this.size() - 1; i++)
        {
            System.out.print(this.get(i).toString() + ", ");
        }
        System.out.println(this.get(this.size() - 1).toString());
    }

    public void TakeCards(Deck decks)
    {
        while(score < 17)
        {
            AddCard(decks);
        }
    }

    public void ResetCards()
    {
        this.clear();
        score = 0;
    }
}
