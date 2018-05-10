using System.Collections.Generic;
using System.Linq;
using BlackjackClassesLib.PlayingEvents;

namespace BlackjackClassesLib
{
    public class Player
    {
        public List<CardsValue> Hand { get; }

        private Deck GameDeck { get; }

        public int Sum { get; protected set; }
        public double Money { get; private set; }
        public double Rate { get; private set; }
        public bool IsBlackjack { get; protected set; }

        public Player(double money, Deck gameDeck)
        {
            Sum = 0;
            GameDeck = gameDeck;
            Money = money;
            Hand = new List<CardsValue>();
        }

        public void Hit()
        {
            Hand.Add(GameDeck.GiveCard());
            Sum += (int)Hand[(Hand.Count - 1)];

            if ((Sum > 21) && (Hand.IndexOf(CardsValue.Ace) >= 0))
            {
                Hand[Hand.IndexOf(CardsValue.Ace)] = Hand[Hand.IndexOf(CardsValue.Ace)] - 10;
                Sum -= 10;
            }

        }

        public int Stand()
        {
            Hand.Clear();
            return Sum;

        }
        /*
        public Player Split()
        {
            Money -= Rate;
            Player newPlayer = new Player(Rate);
            Hand.RemoveAt(Hand.Count - 1);
            newPlayer.Hit();
            return newPlayer;
        }
        */
        public int DoubleDown()
        {
            Money -= Rate;
            Rate *= 2;
            Hit();
            return Stand();
        }

        public int Surrender()
        {
            Money += Rate / 2;
            Hand.Clear();
            return 22;
        }

        public void MakeRate(int valueRate)
        {
            Rate = valueRate;
            Money -= Rate;
        }

        public void AddMoney(double valueMoney)
        {
            Money += valueMoney;
        }
    }
}
