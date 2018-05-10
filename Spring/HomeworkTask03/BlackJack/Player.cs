namespace BlackJack
{
    public abstract class Player
    {
        #region fields
        private readonly string  name;

        private bool    finished;
        private bool    lost;
        private bool    blackjack;

        private int     money;
        private int     bet;

        private int     cardsSum;
        #endregion

        #region properties
        public string Name
        {
            get
            {
                return name;
            }
        }

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
                return cardsSum;
            }
        }

        public int Bet
        {
            get
            {
                return bet;
            }
        }

        public bool Lost
        {
            get
            {
                return lost;
            }
        }

        public bool BlackJack
        {
            get
            {
                return blackjack;
            }
        }
        #endregion

        #region constructor
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="startMoney">player's starting amount of money</param>
        /// <param name="name">player's name</param>
        public Player(int startMoney, string name)
        {
            money = startMoney;
            this.name = name;
        }
        #endregion

        #region methods
        #region logic
        /// <summary>
        /// Start play the game
        /// </summary>
        internal void Start()
        {
            bet = CalculateBet();

            if (bet == 0)
            {
                finished = true;
                lost = true;
            }

            finished = false;
            lost = false;
            blackjack = false;

            cardsSum = 0;

            TakeCard();
            TakeCard();

            // blackjack
            if (cardsSum == 21)
            {
                blackjack = true;
                finished = true;
            }
        }

        /// <summary>
        /// Update logic
        /// </summary>
        /// <returns></returns>
        internal bool Update()
        {
            if (cardsSum > 21 || finished)
            {
                return false;
            }

            switch (MakeDecision())
            {
                case Decision.Hit:
                    Hit();
                    break;
                case Decision.Stand:
                    Stand();
                    break;
                case Decision.DoubleDown:
                    DoubleDown();
                    break;
                case Decision.Surrender:
                    Surrender();
                    break;
            }

            return true;
        }
        #endregion

        #region money management
        /// <summary>
        /// Return bet
        /// </summary>
        internal void Win()
        {
            money += bet;
        }

        /// <summary>
        /// Return bet with multiplier
        /// </summary>
        /// <param name="multiplier"></param>
        internal void Win(float multiplier)
        {
            money += (int)(bet * multiplier);
        }

        /// <summary>
        /// Lose bet
        /// </summary>
        internal void Lose()
        {
            money -= bet;
        }
        #endregion

        #region inheritable
        /// <summary>
        /// Player's logic
        /// </summary>
        /// <returns>player's decision</returns>
        protected abstract Decision MakeDecision();

        /// <summary>
        /// Player's bet
        /// </summary>
        /// <returns>bet</returns>
        protected abstract int CalculateBet();        
        #endregion

        #region decisions
        private void Hit()
        {
            TakeCard();
        }

        private void Stand()
        {
            finished = true;
        }

        private void DoubleDown()
        {
            bet *= 2;
            TakeCard();

            finished = true;
        }

        private void Surrender()
        {
            bet = bet / 2;

            lost = true;
            finished = true;
        }
        #endregion

        private void TakeCard()
        {
            Card card = Game.Instance.Deck.GetCard();
            cardsSum += Deck.GetCardValue(card, cardsSum);
        }
        #endregion
    }
}
