using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    internal sealed class Dealer
    {
        private readonly List <int> _dealersHand;
        private int _sum;
        public bool IsBlackjack { get; set; }

        public Dealer(List<int> gameDeck)
        {
            _dealersHand = new List<int>
            {
                gameDeck.Last()
            };
            gameDeck.RemoveAt(gameDeck.Count - 1);
            _sum += _dealersHand[(_dealersHand.Count - 1)];

            _dealersHand.Add(gameDeck[gameDeck.Count-1]);
            gameDeck.RemoveAt(gameDeck.Count - 1);
            _sum += _dealersHand[(_dealersHand.Count - 1)];

            if (_sum == 21)
            {
                IsBlackjack = true;
            }
        }


        public int DealersPlay(List<int> gameDeck)
        {
            while (_sum <= 17)
            {
                _dealersHand.Add(gameDeck.Last());
                gameDeck.RemoveAt(gameDeck.Count - 1);
                _sum += _dealersHand[(_dealersHand.Count - 1)];
                if (_sum > 21 && (_dealersHand.IndexOf((int)CardsValue.Ace) >= 0))
                {
                    _dealersHand[_dealersHand.IndexOf((int)CardsValue.Ace)] = _dealersHand[_dealersHand.IndexOf((int)CardsValue.Ace)] - 10;
                    _sum -= 10;
                }
            }
            return _sum;
        }

    }
}
