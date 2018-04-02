using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class Dealer
    {
        private List <int> _dealers_hand;
        private int _sum;

        public Dealer(List<int> gameDeck)
        {
            _dealers_hand = new List<int>
            {
                gameDeck.Last()
            };
            gameDeck.RemoveAt(gameDeck.Count - 1);
            _sum += _dealers_hand[(_dealers_hand.Count - 1)];

            _dealers_hand.Add(gameDeck[gameDeck.Count-1]);
            gameDeck.RemoveAt(gameDeck.Count - 1);
            _sum += _dealers_hand[(_dealers_hand.Count - 1)];

        }


        public int DealersPlay(List<int> gameDeck)
        {
            while (_sum <= 17)
            {
                _dealers_hand.Add(gameDeck.Last());
                gameDeck.RemoveAt(gameDeck.Count - 1);
                _sum += _dealers_hand[(_dealers_hand.Count - 1)];
                if (_sum > 21 && (_dealers_hand.IndexOf(11) >= 0))
                {
                    _dealers_hand[_dealers_hand.IndexOf(11)] = _dealers_hand[_dealers_hand.IndexOf(11)] - 10;
                    _sum -= 10;
                }
            }
            return _sum;
        }

    }
}
