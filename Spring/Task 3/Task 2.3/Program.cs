using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("У обоих ботов изначально 1000 фишек.\n");
            var resultFirstBot = new List<int>();
            for (int i = 0; i < 1000; i++)
            {
                var firstBot = new BotWithFirstAlgorithm();
                var gameBot = new Game<BotWithFirstAlgorithm>(firstBot);
                gameBot.StartGame();
                resultFirstBot.Add(firstBot.Chips);
            }
            Console.WriteLine("За 1000 игр у первого бота остается в среденем {0} фишек.\n", resultFirstBot.Average());
            var resultSecondBot = new List<int>();
            for (int i = 0; i < 1000; i++)
            {
                var secondBot = new BotWithSecondAlgorithm();
                var gameBot = new Game<BotWithSecondAlgorithm>(secondBot);
                gameBot.StartGame();
                resultSecondBot.Add(secondBot.Chips);
            }
            Console.WriteLine("У второго бота остается в среденем {0} фишек.\n", resultSecondBot.Average());
            Console.WriteLine("Для начала игры нажмите любую клавишу.");
            Console.ReadKey();
            Console.Clear();
            var player = new Player();
            var gamePlayer = new Game<Player>(player);
            gamePlayer.StartGame();
        }
    }
}
