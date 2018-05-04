using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    internal class Player
    {
        public List<CardsValue> Hand { get; set; }

        private Deck GameDeck { get; set; }

        public int Sum { get; set; }
        public double Money { get; set; }
        public double Rate { get; private set; }
        public bool IsBlackjack { get; set; }


        public Player(double money, Deck gameDeck)
        {
            Sum = 0;
            GameDeck = gameDeck;
            Money = money;
            Hand = new List<CardsValue>();
        }


        public void Hit()
        {
            Hand.Add(GameDeck.DeckContent.Last());
            GameDeck.DeckContent.RemoveAt(GameDeck.DeckContent.Count - 1);
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

        public Player Split()
        {
            Money -= Rate;
            Player newPlayer = new Player(Rate,GameDeck);
            GameDeck.DeckContent.Add(Hand[Hand.Count -1]);
            Hand.RemoveAt(Hand.Count - 1);
            newPlayer.Hit();
            return newPlayer;
        }

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


        
    }
}
