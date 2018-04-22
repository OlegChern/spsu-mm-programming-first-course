using System;
using System.Collections.Generic;

namespace BlackJack
{
    class Deck
    {
        const int deckCount = 8;
        private Stack<Card> deck;

        /// <summary>
        /// Creates and shuffles deck
        /// </summary>
        public Deck()
        {
            deck = new Stack<Card>();

            for (int i = 0; i < deckCount; i++)
            {
                for (int suit = 0; suit < 4; suit++)
                {
                    int[] shuffle = Shuffle(13);

                    for (int type = 0; type < 13; type++)
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
        public Card GetCard()
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

        // Knuth shuffle
        private int[] Shuffle(int count)
        {
            Random random = new Random();
            int[] shuffle = new int[count];

            for (int i = 0; i < count; i++)
            {
                shuffle[i] = i;
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