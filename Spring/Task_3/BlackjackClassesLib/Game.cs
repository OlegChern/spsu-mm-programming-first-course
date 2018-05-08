namespace BlackjackClassesLib
{
    public class Game
    {
        public Deck GameDeck { get; }

        private bool isInitEvents;

        public Game(int numberOfDecks)
        {
            GameDeck = new Deck(numberOfDecks);
            GameDeck.ShuffleDeck();
            isInitEvents = false;
        }

        public void PlayGame(params Bot[] BotsArr)
        {
            if (GameDeck.DeckContent.Count <= 100)
            {
                GameDeck.ShuffleDeck();
            }

            if (!isInitEvents)
            {
                Dealer.CardWasTaked += (sender, args) =>
                {
                    GameDeck.DeckContent.RemoveAt(GameDeck.DeckContent.Count - 1);
                };
            }

            if (!isInitEvents)
            {
                foreach (var bot in BotsArr)
                {
                    bot.CardWasTaked += (sender, args) =>
                    {
                        GameDeck.DeckContent.RemoveAt(GameDeck.DeckContent.Count - 1);
                    };
                }
                isInitEvents = true;
            }

            Dealer dealerPlayer = new Dealer(GameDeck.DeckContent[GameDeck.DeckContent.Count - 1]);
            
            foreach (Bot botPlayer in BotsArr)
            {
                botPlayer.Strategy(dealerPlayer.FirstCard);
            }
            
            dealerPlayer.DealersPlay(GameDeck);

            foreach (Bot botPlayer in BotsArr)
            {
                if (botPlayer.IsBlackjack)
                {
                    botPlayer.AddMoney(botPlayer.Rate);
                    if (!dealerPlayer.IsBlackjack)
                    {
                        botPlayer.AddMoney(3 * botPlayer.Rate / 2);
                    }
                }

                else if (botPlayer.Sum <= 21 && dealerPlayer.Sum > 21)
                {
                    botPlayer.AddMoney(2 * botPlayer.Rate);
                }

                else if (botPlayer.Sum <= 21 && dealerPlayer.Sum <= 21 && botPlayer.Sum >= dealerPlayer.Sum)
                {
                    botPlayer.AddMoney(botPlayer.Rate);
                    if (botPlayer.Sum != dealerPlayer.Sum)
                    {
                        botPlayer.AddMoney(botPlayer.Rate);
                    }
                }
            }
        }
    }
}
 