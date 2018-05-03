namespace BlackJack
{
    /// <summary>
    /// BlackJack game singleton class
    /// </summary>
    public class Game
    {
        #region constants
        private const float BlackjackMultiplier = 1.5f;
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
                if (instance == null)
                {
                    instance = new Game();
                }

                return instance;
            }
        }

        public Deck Deck
        {
            get
            {
                return deck;
            }
        }

        public Dealer Dealer
        {
            get
            {
                return dealer;
            }
        }
        #endregion

        #region constructor
        private Game() { }
        #endregion

        #region game logic
        /// <summary>
        /// Starts new game
        /// </summary>
        /// <param name="players">participating players</param>
        public void Start(params Player[] players)
        {
            deck = new Deck();

            dealer = new Dealer();
            dealer.Start();

            this.players = players;
            foreach(Player player in this.players)
            {
                player.Start();
            }

            Update();
        }

        /// <summary>
        /// Game loop
        /// </summary>
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
                    player.Win(BlackjackMultiplier);
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
