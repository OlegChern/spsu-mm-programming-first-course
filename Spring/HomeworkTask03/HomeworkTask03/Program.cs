using System;
using BlackJack;

namespace HomeworkTask03
{
    static class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Blackjack with basic rules and 8 decks of 52 cards.");
            Console.WriteLine("Bots have 3 different strategies. Initial amount of money is 100$.\n");
            Console.WriteLine("Bots' remaining money after 40 bets:");

            const int initMoney = 100;
            const int botsCount = 3;

            Player[] bots = new Player[botsCount];
            int[] botsMoney = new int[botsCount];

            for (int i = 0; i < 40; i++)
            {
                bots[0] = new FearfulBot(initMoney);
                bots[1] = new RiskyBot(initMoney);
                bots[2] = new SmartBot(initMoney);

                Game game = new Game(bots);
                game.Start();

                botsMoney[0] += bots[0].Money;
                botsMoney[1] += bots[1].Money;
                botsMoney[2] += bots[2].Money;
            }

            #region printing results
            for (int i = 0; i < botsCount; i++)
            {
                Console.WriteLine("  " + bots[i].Name + ": " + (botsMoney[i] / 40f).ToString("F") + "$");
            }
            #endregion
        }
    }
}
