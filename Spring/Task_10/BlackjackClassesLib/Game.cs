namespace BlackjackClassesLib
{
    public class Game
    {
        public Deck GameDeck { get; }

        public Game(int numberOfDecks)
        {
            GameDeck = new Deck(numberOfDecks);
            GameDeck.ShuffleDeck();
        }

        public void PlayGame(params Bot[] BotsArr)
        {
            if (GameDeck.DeckContent.Count <= 100)
            {
                GameDeck.ShuffleDeck();
            }
            
            Dealer dealerPlayer = new Dealer(GameDeck.GiveCard());
            
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
 