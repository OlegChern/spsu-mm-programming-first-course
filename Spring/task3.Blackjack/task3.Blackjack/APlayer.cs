using System;
using System.Collections.Generic;


namespace Task3.Blackjack
{
    public abstract class APlayer
    {
        public readonly string name;

        private List<Card> cards;

        public double Money { get; private set; }

        public int SumCards { get; private set; }

        public void ChangeAmountOfMoney(double value)
        {
            Money = Money + value;
        }

        public APlayer(string name, double money)
        {
            this.name = name;
            Money = money;
            cards = new List<Card>();
            SumCards = 0;
        }

        public abstract Action Play(Card dealersFirstCard);

        public void Print()
        {
            Console.Write("{0}: {1} cards: ", name, cards.Count);
            for (int i = 0; i < cards.Count - 1; i++)
            {
                cards[i].Print();
                Console.Write(", ");
            }
            cards[cards.Count - 1].Print();
        }

        public void AddCard(Card card)
        {
            cards.Add(card);
            SumCards += card.GetValueOfCard();
        }

        public void ResetCards()
        {
            cards.Clear();
            SumCards = 0;
        }
    }
}
