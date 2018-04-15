using System;
using System.Collections.Generic;

namespace BlackJack
{
    public enum Card
    {
        Ace = 1,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    }

    class Deck
    {
        const int deckCount = 8;
        private Stack<Card> deck;

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

        public Card Pop()
        {
            return deck.Pop();
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