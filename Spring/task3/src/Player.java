import java.util.LinkedList;

public abstract class Player extends LinkedList<Card>
{
    String name;

    public double Money;

    public double getMoney() {
        return Money;
    }

    public void setMoney(double money) {
        Money = money;
    }

    public int score;

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        score = score;
    }

    public void ChangeAmountOfMoney(double value)
    {
        Money = Money + value;
    }

    public Player(String name, double money)
    {
        this.name = name;
        Money = money;
        score = 0;
    }

    public abstract Action Play(Card dealersFirstCard);


    public void AddCard(Card card)
    {
        this.add(card);
        score += card.getScore();
    }

    public void PrintInfo()
    {
        System.out.println(name + " " + this.size() +" cards ");
        for (int i = 0; i < this.size() - 1; i++)
        {
            System.out.println(this.get(i).toString() + ", ");
        }
        System.out.println(this.get(this.size() - 1).toString());
    }


    public void ResetCards()
    {
        this.clear();
        score = 0;
    }
}
