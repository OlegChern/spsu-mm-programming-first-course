using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
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
            for (int i = 0; i < 15; i++)
            {


                PlayGame(GameDeck, FirstPlayer);
            }

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

        static void PlayGame(List <int> gameDeck, FirstBot FirstPlayer)
        {
            int DealersFirstCard = gameDeck[gameDeck.Count - 1];
            Dealer DealerPlayer = new Dealer(gameDeck);
            
            int PlayerSum = FirstPlayer.FirstStrategy(DealersFirstCard);
            int DealerSum = DealerPlayer.DealersPlay(gameDeck);

            if (FirstPlayer.IsBlackjack)
            {
                FirstPlayer.Money += FirstPlayer.Rate;
                if (!DealerPlayer.IsBlackjack)
                {
                    FirstPlayer.Money += 3 * FirstPlayer.Rate / 2;
                }
            }

            if (PlayerSum <= 21 && DealerSum > 21)
            {
                FirstPlayer.Money += 2 * FirstPlayer.Rate;
            }

            else if (PlayerSum<=21 && DealerSum <=21 && PlayerSum >= DealerSum)
            {
                FirstPlayer.Money += FirstPlayer.Rate;
                if (PlayerSum != DealerSum)
                {
                    FirstPlayer.Money += FirstPlayer.Rate;
                }
            }

            Console.WriteLine("Dealer: {0} Player: {1} IsBlackjack: {2}  PlayerMoney: {3} ",DealerSum,PlayerSum,FirstPlayer.IsBlackjack,FirstPlayer.Money);

            DealerPlayer.DealersPlay(gameDeck);
        }
    }
}
