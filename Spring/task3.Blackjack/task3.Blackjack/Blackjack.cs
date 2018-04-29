using System;
using System.Collections.Generic;


namespace Task3.Blackjack
{
    public class Blackjack
    {
        private const int standardBet = 100;

        private const int standardNumberOfDecks = 8;

        private Dealer dealer;

        private Decks decks;

        private List<APlayer> players;

        private int bet;

        public Blackjack(APlayer firstPlayer, APlayer secondPlayer)
        {
            dealer = new Dealer();
            decks = new Decks(standardNumberOfDecks);
            bet = standardBet;
            players = new List<APlayer>();
            players.Add(firstPlayer);
            if (secondPlayer != null)
            {
                players.Add(secondPlayer);
            }
        }

        public void PrintResult()
        {
            Console.WriteLine("Game over");
            dealer.Print();
            Console.WriteLine();
            foreach(APlayer temp in players)
            {
                temp.Print();
                Console.WriteLine();
                Console.Write("{0}: money: ", temp.name);
                double tmp = StopPlay(temp);
                if(tmp > 0)
                {
                    Console.WriteLine("+{0}", tmp);
                }
                else
                {
                    Console.WriteLine(tmp);
                }
            }
            Console.WriteLine();
        }

        private double StopPlay(APlayer player)
        {
            if(player.SumCards == 21)
            {
                if(dealer.SumCards == 21)
                {
                    return 0;
                }
                return bet * 3 / 2;
            }

            if(dealer.SumCards > 21)
            {
                if(player.SumCards > 21)
                {
                    return 0;
                }
                return bet;
            }

            if ((player.SumCards > 21) || (player.SumCards < dealer.SumCards))
            {
                return -bet;
            }
            if(player.SumCards == dealer.SumCards)
            {
                return 0;
            }
            return bet;
        }

        private void Finish()
        {
            foreach(APlayer temp in players)
            {
                temp.ChangeAmountOfMoney(StopPlay(temp));
            }
        }

        public void PlayBlackjack(bool print)
        {
            decks.Shuffle();
            dealer.Dealing(players, decks);
            if(print)
            {
                Console.Write("Dealer's first card: ");
                dealer.FirstCard.Print();
                Console.WriteLine();
                foreach (APlayer temp in players)
                {
                    temp.Print();
                    Console.WriteLine();
                }
                Console.WriteLine();
            }
            
            if(dealer.FirstCard.GetValueOfCard() > 9)
            {
                if(dealer.SumCards >= 21)
                {
                    Finish();
                    return;
                }
            }

            foreach(APlayer temp in players)
            {
                bool stop = false;
                while (!stop)
                {
                    if(temp.SumCards >= 21)
                    {
                        stop = true;
                        break;
                    }
                    if(temp.Play(dealer.FirstCard) == Action.Stand)
                    {
                        stop = true;
                    }
                    else
                    {
                        dealer.GiveCard(temp, decks);
                    }
                }
            }

            dealer.TakeCards(decks);
            Finish();
        }

        public void PrintMoney()
        {
            foreach (APlayer temp in players)
            {
                Console.WriteLine("{0}: money: {1}", temp.name, temp.Money);
            }
        }

        public void Reset()
        {
            foreach (APlayer temp in players)
            {
                temp.ResetCards();
            }
            dealer.ResetCards();
        }
    }
}
