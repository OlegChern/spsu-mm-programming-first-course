using System;
using Unity;
using Unity.Injection;
using Microsoft.Practices.Unity.Configuration;
using BlackJack;
using BlackJack.Bots;

namespace HomeworkTask10
{
    static class Program
    {
        const int BotsCount = 3;

        static void Main(string[] args)
        {
            IUnityContainer container = new UnityContainer();
            container.LoadConfiguration();

            Console.WriteLine("Blackjack with basic rules and 8 decks of 52 cards.");
            Console.WriteLine("Bots have 3 different strategies. Initial amount of money is 100$.\n");
            Console.WriteLine("Bots' remaining money after 40 bets:");

            Player[] bots = new Player[BotsCount];
            int[] botsMoney = new int[BotsCount];

            for (int i = 0; i < 40; i++)
            {
                bots[0] = container.Resolve<FearfulBot>();
                bots[1] = container.Resolve<RiskyBot>("riskyBot");
                bots[2] = container.Resolve<SmartBot>("smartBot");

                Game.Instance.Start(bots);

                botsMoney[0] += bots[0].Money;
                botsMoney[1] += bots[1].Money;
                botsMoney[2] += bots[2].Money;
            }

            #region printing results
            for (int i = 0; i < BotsCount; i++)
            {
                Console.WriteLine("  " + bots[i].Name + ": " + (botsMoney[i] / 40f).ToString("F") + "$");
            }
            #endregion
        }
    }
}
