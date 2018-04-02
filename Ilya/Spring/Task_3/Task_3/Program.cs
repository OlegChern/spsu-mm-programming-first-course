using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class Program
    {
        static void Main(string[] args)
        {
            double sum1 = 0;
            double sum2 = 0;


            List<int> GameDeck = ShuffleDeck();

            Bot FirstPlayer = new Bot(500, GameDeck);
            Bot SecondPlayer = new Bot(500, GameDeck);


            for (int i = 0; i < 40; i++)
            {
                if (GameDeck.Count <= 35)
                {
                    GameDeck.Clear();
                    GameDeck.AddRange(ShuffleDeck());
                }

                PlayGame(GameDeck, FirstPlayer, SecondPlayer);

                sum2 += SecondPlayer.Money;
                sum1 += FirstPlayer.Money;
            }


            Console.WriteLine(sum1/40);
            Console.WriteLine(sum2/40);

        }

        static List<int> ShuffleDeck()
        {
            Deck NotMixedDeck = new Deck();
            List<int> ShuffledDeck = new List<int>();
            Random MyR = new Random();
            for (int i = 0; i < Deck.DeckSize; i++)
            {
                ShuffledDeck.Add(NotMixedDeck.TakeRandomCard(MyR));
            }

            return ShuffledDeck;
        }

        static void PlayGame(List <int> gameDeck, Bot FirstPlayer, Bot SecondPlayer)
        {
            int DealersFirstCard = gameDeck[gameDeck.Count - 1];
            Dealer DealerPlayer = new Dealer(gameDeck);
            DealerPlayer.DealersPlay(gameDeck);
            Payment(FirstPlayer, DealerPlayer, DealersFirstCard, gameDeck);
            Payment(SecondPlayer, DealerPlayer, DealersFirstCard, gameDeck);

        }

        static void Payment(Bot player, Dealer dealer, int dealersFirstCard,List <int> gameDeck)
        {
            int playerSum = player.FirstStrategy(dealersFirstCard);

            int dealerSum = dealer.DealersPlay(gameDeck);

            if (player.IsBlackjack)
            {
                player.Money += player.Rate;
                if (!dealer.IsBlackjack)
                {
                    player.Money += 3 * player.Rate / 2;
                }
            }

            else if (playerSum <= 21 && dealerSum > 21)
            {
                player.Money += 2 * player.Rate;
            }

            else if (playerSum <= 21 && dealerSum <= 21 && playerSum >= dealerSum)
            {
                player.Money += player.Rate;
                if (playerSum != dealerSum)
                {
                    player.Money += player.Rate;
                }
            }


        }

    }
}
