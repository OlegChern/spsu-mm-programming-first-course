using System;
using System.Collections.Generic;
using System.Linq;

namespace task3
{
    class Dealer
    {
        private List<Card> hand;

        public Card FirstCard
        {
            get
            {
                if (hand != null && hand.Any())
                {
                    return hand[0];
                }
                throw new InvalidOperationException("Attempt to access first card before it has been given.");
            }
        }

        public Dealer(List<Card> deck)
        {
            hand = new List<Card>
            {
                deck[0]
            };
            deck.RemoveAt(0);
        }

        public void TakeEnoughCards(List<Card> deck)
        {
            if (Score() < 17)
            {
                hand.Add(deck[0]);
                deck.RemoveAt(0);
                TakeEnoughCards(deck);
            }
        }

        public uint Score() => Card.GetScore(hand);

        public void WriteCards(string message = null)
        {
            if (message != null)
            {
                Console.Write(message);
            }
            for (int i = 0; i < hand.Count; i++)
            {
                Console.Write(hand[i]);
                if (i == hand.Count - 2)
                {
                    Console.Write(" and ");
                }
                else if (i != hand.Count - 1)
                {
                    Console.Write(", ");
                }
            }
        }
    }
}
