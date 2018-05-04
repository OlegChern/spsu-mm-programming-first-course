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
        private readonly List <CardsValue> _dealersHand;
        private int _sum;
        public bool IsBlackjack { get; set; }

        public Dealer(Deck gameDeck)
        {
            _dealersHand = new List<CardsValue>
            {
                gameDeck.DeckContent.Last()
            };
            gameDeck.DeckContent.RemoveAt(gameDeck.DeckContent.Count -1);
            _sum += (int)_dealersHand[_dealersHand.Count - 1];

            _dealersHand.Add(gameDeck.DeckContent[gameDeck.DeckContent.Count - 1]);
            gameDeck.DeckContent.RemoveAt(gameDeck.DeckContent.Count - 1);
            _sum += (int)_dealersHand[(_dealersHand.Count - 1)];

            if (_sum == 21)
            {
                IsBlackjack = true;
            }
        }


        public int DealersPlay(Deck gameDeck)
        {
            while (_sum <= 17)
            {
                _dealersHand.Add(gameDeck.DeckContent.Last());
                gameDeck.DeckContent.RemoveAt(gameDeck.DeckContent.Count - 1);
                _sum += (int)_dealersHand[(_dealersHand.Count - 1)];
                if (_sum > 21 && (_dealersHand.IndexOf(CardsValue.Ace) >= 0))
                {
                    _dealersHand[_dealersHand.IndexOf(CardsValue.Ace)] = _dealersHand[_dealersHand.IndexOf(CardsValue.Ace)] - 10;
                    _sum -= 10;
                }
            }
            return _sum;
        }

    }
}
