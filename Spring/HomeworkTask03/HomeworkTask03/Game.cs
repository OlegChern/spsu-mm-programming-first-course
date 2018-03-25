using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public enum Card
    {
        Ace = 1,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    }

    public class Game
    {
        #region constants
        private const int DefaultBotMoney = 300;
        #endregion

        #region fields
        private Stack<Card> deck;
        private Player[] players;

        private Card[] dealerCards = new Card[2];

        private static Game instance;
        #endregion

        #region constructor
        public Game(int playerCount)
        {
            instance = this;

            deck = CreateDeck();
            players = new Player[playerCount];
        }
        #endregion

        #region game logic
        public void Start()
        {
            // init players
            for (int i = 0; i < players.Length; i++)
            {
                players[i] = new Bot(DefaultBotMoney);
            }

            // 0 is dealer's index
            dealerCards[0] = GetCard();
            dealerCards[1] = GetCard();

            if (dealerCards[0] != Card.Ace)
            {
                // every player take 2 cards
                foreach (Player player in players)
                {
                    player.TakeCard(GetCard());
                    player.TakeCard(GetCard());
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
            foreach (Player player in players)
            {
                player.MakeDecision();
                player.TakeCard(GetCard());
            }

            Update();
        }
        #endregion

        #region public methods
        public void Stop()
        {

        }

        public static Card GetCard()
        {
            return instance.deck.Pop();
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

        #region init methods
        private Stack<Card> CreateDeck()
        {
            Stack<Card> resultDeck = new Stack<Card>();

            for (int deck = 0; deck < 8; deck++)
            {
                for (int suit = 0; suit < 4; suit++)
                {
                    int[] shuffle = GetShuffle(13);

                    for (int type = 0; type < 13; type++)
                    {
                        resultDeck.Push((Card)shuffle[type]);
                    }
                }
            }

            return resultDeck;
        }

        // Knuth shuffle
        private int[] GetShuffle(int count)
        {
            Random random = new Random();
            int[] shuffle = new int[count];

            for (int j = 13; j > 1; j--)
            {
                int k = random.Next(j);

                int temp = shuffle[j];
                shuffle[j] = shuffle[k];
                shuffle[k] = temp;
            }

            return shuffle;
        }
        #endregion
    }
}
