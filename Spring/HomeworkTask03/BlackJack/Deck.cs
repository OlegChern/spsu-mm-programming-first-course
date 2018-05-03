using System;
using System.Collections.Generic;

namespace BlackJack
{
    public class Deck
    {
        const int SuitsCount = 4;
        const int CardsCount = 13;
        const int DeckCount = 8;

        private Stack<Card> deck;

        /// <summary>
        /// Creates and shuffles deck
        /// </summary>
        internal Deck()
        {
            deck = new Stack<Card>();

            for (int i = 0; i < DeckCount; i++)
            {
                for (int suit = 0; suit < SuitsCount; suit++)
                {
                    int[] shuffle = Shuffle(CardsCount);

                    for (int type = 0; type < CardsCount; type++)
                    {
                        deck.Push((Card)shuffle[type]);
                    }
                }
            }
        }

        /// <summary>
        /// Get one card from the deck
        /// </summary>
        /// <returns></returns>
        internal Card GetCard()
        {
            return deck.Pop();
        }

        /// <summary>
        /// Get value of the card
        /// </summary>
        /// <param name="card">card to get value</param>
        /// <returns></returns>
        public static int GetCardValue(Card card)
        {
            switch (card)
            {
                case Card.King:
                case Card.Queen:
                case Card.Jack:
                case Card.Ten:
                    return 10;
                default:
                    return (int)card;
            }
        }

        /// <summary>
        /// Get value of the card
        /// </summary>
        /// <param name="card">card to get value</param>
        /// <param name="cardsSum">sum of cards to calculate ace value</param>
        /// <returns></returns>
        public static int GetCardValue(Card card, int cardsSum)
        {
            if (card == Card.Ace)
            {
                return cardsSum + 11 > 21 ? 1 : 11;
            }
            else
            {
                return GetCardValue(card);
            }
        }

        /// <summary>
        /// Knuth shuffle
        /// </summary>
        /// <param name="count">amount of numbers to shuffle</param>
        /// <returns>shuffled sequence</returns>
        private static int[] Shuffle(int count)
        {
            Random random = new Random();
            int[] shuffle = new int[count];

            for (int i = 0; i < count; i++)
            {
                shuffle[i] = i + 1;
            }

            for (int i = count - 1; i > 0; i--)
            {
                int j = random.Next(i + 1);

                int temp = shuffle[i];
                shuffle[i] = shuffle[j];
                shuffle[j] = temp;
            }

            return shuffle;
        }

    }
}