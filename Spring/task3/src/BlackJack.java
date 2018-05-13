import java.util.LinkedList;

public class BlackJack extends LinkedList<Player>
{
    private static int standardBet = 100;

    private static int standardNumberOfDecks = 8;

    private Dealer dealer;

    private Deck decks;

    private int bet;

    public BlackJack(Player firstPlayer, Player secondPlayer)
    {
        dealer = new Dealer();
        decks = new Deck(standardNumberOfDecks);
        bet = standardBet;
        this.add(firstPlayer);
        if (secondPlayer != null)
        {
            this.add(secondPlayer);
        }
    }

    public void PrintResult()
    {
        System.out.println("Game over");
        dealer.PrintInfo();
        for(Player p : this)
        {
            p.PrintInfo();
            System.out.println(p.name + " money ");
            int tmp = StopPlay(p);
            if(tmp > 0)
            {
                System.out.println ("+" + tmp);
            }
            else
            {
                System.out.println (tmp);
            }
        }
    }

    private int StopPlay(Player player)
    {
        if(player.score == 21)
        {
            if(dealer.score == 21)
            {
                return 0;
            }
            return bet * 3 / 2;
        }

        if(dealer.score > 21)
        {
            if(player.score > 21)
            {
                return 0;
            }
            return bet;
        }

        if ((player.score > 21) || (player.score < dealer.score))
        {
            return -bet;
        }
        if(player.score == dealer.score)
        {
            return 0;
        }
        return bet;
    }

    private void Finish()
    {
        for (Player p : this)
        {
            p.ChangeAmountOfMoney(StopPlay(p));
        }
    }

    public void PlayBlackjack(boolean print)
    {
        dealer.Dealing(this, decks);
        if(print)
        {
            System.out.println("Dealer's first card: ");
            System.out.println(dealer.firstCard);
            for (Player p : this)
            {
                p.PrintInfo();
            }
        }

        if(dealer.firstCard.getScore() > 9)
        {
            if(dealer.score >= 21)
            {
                Finish();
                return;
            }
        }

        for (Player p : this)
        {
            boolean stop = false;
            while (!stop)
            {
                if(p.score >= 21)
                {
                    stop = true;
                    break;
                }
                if(p.Play(dealer.firstCard) == Action.STAND)
                {
                    stop = true;
                }
                else
                {
                    dealer.GiveCard(p, decks);
                }
            }
        }

        dealer.TakeCards(decks);
        Finish();
    }

    public void PrintMoney()
    {
        for (Player p : this)
        {
            System.out.println(p.name + " money " + p.Money);
        }
    }

    public void Reset()
    {
        for (Player p : this)
        {
            p.ResetCards();
        }
        dealer.ResetCards();
    }
}

