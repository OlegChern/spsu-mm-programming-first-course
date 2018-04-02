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
    class Player
    {
        public List<int> Hand { get; set; }

        private readonly List<int> _game_deck;

        private int _sum = 0;

        public int Sum
        {
            get { return _sum; }
            set { _sum = value; }
        }

        public double Money { get; set; }
        public double Rate { get; set; }
        public bool IsBlackjack { get; set; }


        public Player(double money, List<int> gameDeck)
        {
            _game_deck = gameDeck;
            Money = money;
            Hand = new List<int>();
        }


        public void Hit()
        {
            Hand.Add(_game_deck.Last());
            _game_deck.RemoveAt(_game_deck.Count - 1);
            _sum += Hand[(Hand.Count - 1)];

            if ((_sum > 21) && (Hand.IndexOf(11) >= 0))
            {
                Hand[Hand.IndexOf(11)] = Hand[Hand.IndexOf(11)] - 10;
                _sum -= 10;
            }

        }

        public int Stand()
        {
            Hand.Clear();
            return _sum;

        }


        public Player Split()
        {
            Money -= Rate;
            List<int> SecondHand = new List<int>();
            SecondHand.Add(Hand[1]);
            Hand.RemoveAt(Hand.Count - 1);
            return new Player(Rate, _game_deck);
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
