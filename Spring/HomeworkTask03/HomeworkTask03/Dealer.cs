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
        #endregion

        /// <summary>
        /// Face-up card
        /// </summary>
        public Card Card
        {
            get
            {
                return cards[0];
            }
        }

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
            Card card = Game.Instance.GetCard();
            cards.Add(card);

            cardsSum += Game.GetCardValue(card, cardsSum);
        }
    }
}
