using System;


namespace Task3.Blackjack
{
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
}
