using System;
using System.Collections.Generic;


namespace task3.Blackjack
{
    public enum Suit { Diamonds, Hearts, Spades, Clubs }

    public enum Value { Ace = 11, King = 10, Queen = 10, Jack = 10,
        Ten = 10, Nine = 9, Eight = 8, Seven = 7, Six = 6, Five = 5, Four = 4, Three = 3, Two = 2 }

    public class Card
    {
        private Suit suit;

        private Value value;

        public Card(Suit suit, Value value)
        {
            this.value = value;
            this.suit = suit;
        }

        public int GetValueOfCard()
        {
            return (int)value;
        }

        public void Print()
        {
            Console.Write("{0} {1}", value, suit);
        }
    }

    public class Decks
    {
        private int numberOfDecks;

        private List<Card> listOfCards;

        public Decks(int numberOfDecks)
        {
            this.numberOfDecks = numberOfDecks;
            this.listOfCards = new List<Card>();

            for (int i = 0; i < numberOfDecks; i++)
            {
                foreach(Value value in Enum.GetValues(typeof(Value)))
                {
                    foreach (Suit suit in Enum.GetValues(typeof(Suit)))
                    {
                        listOfCards.Add(new Card(suit, value));
                    }
                }
            }
        }

        public Card Pop()
        {
            Card card = listOfCards[listOfCards.Count - 1];
            listOfCards.RemoveAt(listOfCards.Count - 1);
            return card;
        }

        public void Shuffle()
        {
            Random rand = new Random();

            int time = rand.Next(listOfCards.Count / 4, listOfCards.Count);

            for (int i = 0; i < time; i++)
            {
                int x = rand.Next(listOfCards.Count - 1);
                int y = rand.Next(listOfCards.Count - 1);

                var temp = listOfCards[x];
                listOfCards[x] = listOfCards[y];
                listOfCards[y] = temp;
            }
        }
    }
}
