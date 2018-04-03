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


            List<int> gameDeck = ShuffleDeck();

            Bot firstPlayer = new Bot(500, gameDeck);
            Bot secondPlayer = new Bot(500, gameDeck);


            for (int i = 0; i < 40; ++i)
            {
                if (gameDeck.Count <= 35)
                {
                    gameDeck.Clear();
                    gameDeck.AddRange(ShuffleDeck());
                }

                PlayGame(gameDeck, firstPlayer, secondPlayer);

                sum2 += secondPlayer.Money;
                sum1 += firstPlayer.Money;
            }


            Console.WriteLine(sum1/40);
            Console.WriteLine(sum2/40);

        }

        private static List<int> ShuffleDeck()
        {
            Deck notMixedDeck = new Deck();
            List<int> shuffledDeck = new List<int>();
            Random myR = new Random();
            for (int i = 0; i < Deck.DeckSize; i++)
            {
                shuffledDeck.Add(notMixedDeck.TakeRandomCard(myR));
            }

            return shuffledDeck;
        }

        private static void PlayGame(List <int> gameDeck, Bot firstPlayer, Bot secondPlayer)
        {
            int dealersFirstCard = gameDeck[gameDeck.Count - 1];
            Dealer dealerPlayer = new Dealer(gameDeck);
            dealerPlayer.DealersPlay(gameDeck);
            Payment(firstPlayer, dealerPlayer, dealersFirstCard, gameDeck);
            Payment(secondPlayer, dealerPlayer, dealersFirstCard, gameDeck);

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
