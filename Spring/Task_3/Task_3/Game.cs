using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    internal class Game
    {
        internal Deck GameDeck { get; }

        public Game(int numberOfDecks)
        {
            GameDeck = new Deck(numberOfDecks);
            GameDeck.ShuffleDeck();
        }

        internal static void PlayGame(Deck gameDeck, params Bot[] BotsArr)
        {
            int dealersFirstCard = (int)gameDeck.DeckContent[gameDeck.DeckContent.Count - 1];
            Dealer dealerPlayer = new Dealer(gameDeck);
            dealerPlayer.DealersPlay(gameDeck);

            foreach (Bot botPlayer in BotsArr)
            {
                Payment(botPlayer, dealerPlayer, dealersFirstCard, gameDeck);
            }
        }

        private static void Payment(Bot player, Dealer dealer, int dealersFirstCard, Deck gameDeck)
        {
            int playerSum = player.Strategy(dealersFirstCard);

            int dealerSum = dealer.DealersPlay(gameDeck);

            if (gameDeck.DeckContent.Count <= 35)
            {
                gameDeck.ShuffleDeck();
            }

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
 