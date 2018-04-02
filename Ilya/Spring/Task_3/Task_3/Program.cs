using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class Program
    {
        static void Main(string[] args)
        {
            List<int> GameDeck = ShuffleDeck();

            FirstBot FirstPlayer = new FirstBot(500,GameDeck);
            SecondBot SecondPlayer = new SecondBot(500, GameDeck);
            PlayGame(GameDeck,FirstPlayer, SecondPlayer);


        }

        static List<int> ShuffleDeck()
        {
            Deck NotMixedDeck = new Deck();
            List<int> ShuffledDeck = new List<int>();
            Random MyR = new Random();
            for (int i = 0; i < Deck.DeckSize; i++)
            {
                ShuffledDeck.Add(NotMixedDeck.TakeRandomCard(MyR));
            }

            return ShuffledDeck;
        }

        static void PlayGame(List <int> gameDeck, FirstBot FirstPlayer, SecondBot SecondPlayer)
        {
            int DealersFirstCard = gameDeck[gameDeck.Count - 1];
            Dealer DealerPlayer = new Dealer(gameDeck);
            FirstPlayer.FirstStrategy(DealersFirstCard);



            DealerPlayer.DealersPlay(gameDeck);
        }
    }
}
