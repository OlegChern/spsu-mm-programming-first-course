namespace BlackJack
{
    class Game
    {
        #region constants
        private const float blackjackMultiplier = 1.5f;
        #endregion

        #region fields
        private Deck deck;
        private Player[] players;

        private Dealer dealer;

        private static Game instance;
        #endregion

        #region properties
        public static Game Instance
        {
            get
            {
                return instance;
            }
        }

        public int DealerCardValue
        {
            get
            {
                int dealerCardValue = GetCardValue(dealer.Card);
                dealerCardValue = dealerCardValue != 1 ? dealerCardValue : 11;

                return dealerCardValue;
            }
        }
        #endregion

        #region constructor
        public Game(params Player[] players)
        {
            instance = this;
            this.players = players;

            deck = new Deck();
        }
        #endregion

        #region game logic
        /// <summary>
        /// Start the game
        /// </summary>
        public void Start()
        {
            dealer = new Dealer();
            dealer.Start();

            for (int i = 0; i < players.Length; i++)
            {
                players[i].Start();
            }

            Update();
        }

        // game loop
        private void Update()
        {
            while (true)
            {
                bool updatable = false;

                foreach (Player player in players)
                {
                    updatable |= player.Update();
                }

                if (!updatable)
                {
                    break;
                }
            }

            // dealer's decisions
            while (dealer.Update()) { }

            Finish();
        }

        private void Finish()
        {
            foreach (Player player in players)
            {
                if (player.Lost)
                {
                    player.Lose();
                }
                else if (player.BlackJack)
                {
                    player.Win(blackjackMultiplier);
                }
                else if (dealer.Lost)
                {
                    player.Win();
                }
                else if (dealer.CardsSum < player.CardsSum)
                {
                    player.Win();
                }
            }
        }
        #endregion

        #region cards methods
        /// <summary>
        /// Get one card from the deck
        /// </summary>
        /// <returns></returns>
        public Card GetCard()
        {
            return deck.Pop();
        }

        /// <summary>
        /// Get value of the card
        /// </summary>
        /// <param name="card">card to get value</param>
        /// <returns></returns>
        public static int GetCardValue(Card card)
        {
            switch (card)
            {
                case Card.King:
                case Card.Queen:
                case Card.Jack:
                case Card.Ten:
                    return 10;
                default:
                    return (int)card;
            }
        }

        /// <summary>
        /// Get value of the card
        /// </summary>
        /// <param name="card">card to get value</param>
        /// <param name="cardsSum">sum of cards to calculate ace value</param>
        /// <returns></returns>
        public static int GetCardValue(Card card, int cardsSum)
        {
            switch (card)
            {
                case Card.King:
                case Card.Queen:
                case Card.Jack:
                case Card.Ten:
                    return 10;
                case Card.Ace:
                    return cardsSum + 11 > 21 ? 1 : 11;
                default:
                    return (int)card;
            }
        }
        #endregion
    }
}
