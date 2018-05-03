using System.Collections.Generic;

namespace BlackJack
{
    public class Dealer
    {
        #region fields
        private int cardsSum;
        private List<Card> cards;
        #endregion

        #region properties
        public bool Lost
        {
            get
            {
                return cardsSum > 21;
            }
        }

        public int CardsSum
        {
            get
            {
                return cardsSum;
            }
        }

        public int FaceUpCardValue
        {
            get
            {
                // cards[0] is face-up card
                int cardValue = Deck.GetCardValue(cards[0]);

                // if ace then 11
                cardValue = cardValue != 1 ? cardValue : 11;

                return cardValue;
            }
        }
        #endregion

        internal Dealer()
        {
            cardsSum = 0;
            cards = new List<Card>();
        }

        /// <summary>
        /// Start play the game
        /// </summary>
        internal void Start()
        {
            TakeCard();
            TakeCard();
        }

        /// <summary>
        /// Update logic
        /// </summary>
        /// <returns></returns>
        internal bool Update()
        {
            if (cardsSum >= 17)
            {
                return false;
            }

            TakeCard();
            return true;
        }

        private void TakeCard()
        {
            Card card = Game.Instance.Deck.GetCard();
            cards.Add(card);

            cardsSum += Deck.GetCardValue(card, cardsSum);
        }
    }
}
