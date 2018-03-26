using System;
using System.Collections.Generic;


namespace task3.Blackjack
{
    public enum Action { hit = 0, stand = 1};

    public abstract class APlayer
    {
        public readonly string name;

        private List<Card> cards;

        private double money;
        public double Money
        {
            get
            {
                return money;
            }
            private set
            {
                money = value;
            }
        }

        private int sumCards;
        public int SumCards
        {
            get
            {
                return sumCards;
            }
            private set
            {
                sumCards = value;
            }
        }

        public void ChangeAmountOfMoney(double value)
        {
            Money = Money + value;
        }

        public APlayer(string name, double money)
        {
            this.name = name;
            this.money = money;
            cards = new List<Card>();
            SumCards = 0;
        }

        public abstract Action Play(Dealer dealer);

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
