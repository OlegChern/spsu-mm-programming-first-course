using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    class Game
    {
        #region constants
        private const int DefaultBotMoney = 300;
        #endregion

        #region fields
        private Deck deck;
        private Player[] players;

        private Card[] dealerCards = new Card[2];

        private static Game instance;
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
        public void Start()
        {
            // 0 is dealer's index
            dealerCards[0] = GetCard();
            dealerCards[1] = GetCard();

            if (dealerCards[0] != Card.Ace)
            {
                // every player take 2 cards
                for (int i = 0; i < players.Length; i++)
                {
                    players[i] = new Bot(this, DefaultBotMoney);
                }

                Update();
            }
            else
            {
                // todo
            }
        }

        private void Update()
        {
            bool updatable = true;

            do
            {
                updatable = false;

                foreach (Player player in players)
                {
                    if (!player.IsFinished)
                    {
                        player.Update();
                        updatable = true;
                    }
                }
            } while (updatable);
        }

        public void Stop()
        {

        }
        #endregion

        #region public methods
        public Card GetCard()
        {
            return deck.Pop();
        }

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
        #endregion
    }
}
