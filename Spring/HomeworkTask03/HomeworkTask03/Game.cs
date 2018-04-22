namespace BlackJack
{
    class Game
    {
        #region constants
        private const float blackjackMultiplier = 1.5f;
        #endregion

        #region fields
        private Deck deck;
        private Dealer dealer;
        private Player[] players;

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

        public static Deck Deck
        {
            get
            {
                return instance.deck;
            }
        }

        public static Dealer Dealer
        {
            get
            {
                return instance.dealer;
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
    }
}
