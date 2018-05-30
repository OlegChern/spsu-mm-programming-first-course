using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Unity;
using Unity.Injection;
using Microsoft.Practices.Unity.Configuration;
using BlackJack;

namespace Task10
{
    class Program
    {
        static void Main(string[] args)
        {
            IUnityContainer container = new UnityContainer();
            container.LoadConfiguration();

            Console.WriteLine("У обоих ботов изначально 1000 фишек.\n");
            var resultFirstBot = new List<int>();
            container.RegisterType<Bot, BotWithFirstAlgorithm>();
            for (int i = 0; i < 1000; i++)
            {
                var gameBot = container.Resolve<Game<Bot>>("gameWithBot");               
                gameBot.StartGame();
                resultFirstBot.Add(gameBot.Player.Chips);
            }
            Console.WriteLine("За 1000 игр у первого бота остается в среденем {0} фишек.\n", resultFirstBot.Average());

            var resultSecondBot = new List<int>();
            container.RegisterType<Bot, BotWithSecondAlgorithm>();
            for (int i = 0; i < 1000; i++)
            {
                var gameBot = container.Resolve<Game<Bot>>("gameWithBot");
                gameBot.StartGame();
                resultSecondBot.Add(gameBot.Player.Chips);
            }
            Console.WriteLine("У второго бота остается в среденем {0} фишек.\n", resultSecondBot.Average());
            Console.WriteLine("Для начала игры нажмите любую клавишу.");
            Console.ReadKey();
            Console.Clear();

            var gamePlayer = container.Resolve<Game<Player>>("gameWithPlayer");
            gamePlayer.StartGame();
        }
    }
}
