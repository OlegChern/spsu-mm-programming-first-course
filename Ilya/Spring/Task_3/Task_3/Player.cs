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
        public List<int> Hand { get; set; }

        private readonly List<int> _gameDeck;

        public int Sum { get; set; }
        public double Money { get; set; }
        public double Rate { get; set; }
        public bool IsBlackjack { get; set; }


        public Player(double money, List<int> gameDeck)
        {
            Sum = 0;
            _gameDeck = gameDeck;
            Money = money;
            Hand = new List<int>();
        }


        public void Hit()
        {
            Hand.Add(_gameDeck.Last());
            _gameDeck.RemoveAt(_gameDeck.Count - 1);
            Sum += Hand[(Hand.Count - 1)];

            if ((Sum > 21) && (Hand.IndexOf((int)CardsValue.Ace) >= 0))
            {
                Hand[Hand.IndexOf((int)CardsValue.Ace)] = Hand[Hand.IndexOf((int)CardsValue.Ace)] - 10;
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
            Player newPlayer = new Player(Rate,_gameDeck);
            _gameDeck.Add(Hand[Hand.Count -1]);
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
