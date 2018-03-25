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

    public abstract class Player
    {
        #region fields
        protected int money;
        protected int bet;

        protected List<Card> cards = new List<Card>();
        #endregion

        #region properties
        public int GetMoney
        {
            get
            {
                return money;
            }
        }

        public int Sum
        {
            get
            {
                int sum = 0;

                foreach(Card card in cards)
                {
                    sum += Game.GetCardValue(card);
                }

                return sum;
            }
        }
        #endregion

        #region constructor
        public Player(int startMoney)
        {
            money = startMoney;
        }
        #endregion

        #region methods
        public void TakeCard(Card card)
        {
            cards.Add(card);
        }

        // player's logic
        public virtual void MakeDecision() { }

        #region decisions
        protected void Hit()
        {
            cards.Add(Game.GetCard());
        }

        /*protected void Stand()
        {

        }*/

        protected void Split()
        {

        }

        protected void DoubleDown()
        {

        }

        protected void Surrender()
        {
            money -= bet / 2;
        }
        #endregion

        protected virtual int AceValue(int cardsSum)
        {
            return cardsSum + 11 > 21 ? 1 : 11;
        }
        #endregion
    }
}
