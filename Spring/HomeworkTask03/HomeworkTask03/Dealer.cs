using System.Collections.Generic;

namespace BlackJack
{
    class Dealer
    {
        #region fields
        private int money;

        private int cardsSum;
        private List<Card> cards;
        #endregion

        #region properties
        public int Money
        {
            get
            {
                return money;
            }
        }

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

        /*public Card FaceUpCard
        {
            get
            {
                return cards[0];
            }
        }*/
        #endregion

        public Dealer()
        {
            money = 0;
            cardsSum = 0;
            cards = new List<Card>();
        }

        /// <summary>
        /// Start play the game
        /// </summary>
        public void Start()
        {
            TakeCard();
            TakeCard();
        }

        /// <summary>
        /// Update logic
        /// </summary>
        /// <returns></returns>
        public bool Update()
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
            Card card = Game.Deck.GetCard();
            cards.Add(card);

            cardsSum += Deck.GetCardValue(card, cardsSum);
        }
    }
}
