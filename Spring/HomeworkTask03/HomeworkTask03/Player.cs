using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public enum Option
    {
        Hit,
        Stand,
        DoubleDown,
        Split,
        Surrender
    }

    abstract class Player
    {
        #region fields
        private Game    game;

        private bool    finished;
        private bool    surrendered;

        private int     money;
        private int     bet;

        protected int   cardsSum;
        // private List<Card> cards = new List<Card>();
        #endregion

        #region properties
        public int Money
        {
            get
            {
                return money;
            }
        }

        public int CardsSum
        {
            get
            {
                /* foreach(Card card in cards)
                {
                    sum += Game.GetCardValue(card);
                } */

                return cardsSum;
            }
        }

        public bool IsFinished
        {
            get
            {
                return surrendered || finished;
            }
        }
        #endregion

        #region constructor
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="game">game to which player refers</param>
        /// <param name="startMoney">player's starting amount of money</param>
        public Player(Game game, int startMoney)
        {
            this.game = game;

            money = startMoney;
            bet = money / 4;

            finished = false;
            surrendered = false;

            cardsSum = 0;

            // initial cards
            TakeCard();
            TakeCard();
        }
        #endregion

        #region methods
        /// <summary>
        /// Update logic and check state
        /// </summary>
        public void Update()
        {
            if (finished || surrendered)
            {
                return;
            }

            if (CardsSum > 21)
            {
                surrendered = true;
                return;
            }

            MakeDecision();
        }

        // player's logic
        protected virtual void MakeDecision() { }

        #region decisions
        protected void Hit()
        {
            TakeCard();
        }

        protected void Stand()
        {
            finished = true;
        }

        protected void DoubleDown()
        {
            bet *= 2;
            TakeCard();

            finished = true;
        }

        protected void Surrender()
        {
            bet = bet / 2;
            surrendered = true;
        }
        #endregion

        protected virtual int AceValue()
        {
            return cardsSum + 11 > 21 ? 1 : 11;
        }

        private void TakeCard()
        {
            Card card = game.GetCard();
            // cards.Add(card);

            cardsSum += Game.GetCardValue(card);
        }
        #endregion
    }
}
