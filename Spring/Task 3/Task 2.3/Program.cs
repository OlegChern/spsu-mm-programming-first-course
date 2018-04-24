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
            var resultBot1 = new List<int>();
            for (int i = 0; i < 1000; i++)
            {
                var bot1 = new Bot1();
                var game1 = new Game<Bot1>(bot1);
                game1.StartGame();
                resultBot1.Add(bot1.Chips);
            }
            Console.WriteLine("За 1000 игр у первого бота остается в среденем {0} фишек.\n", resultBot1.Average());
            var resultBot2 = new List<int>();
            for (int i = 0; i < 1000; i++)
            {
                var bot2 = new Bot2();
                var game2 = new Game<Bot2>(bot2);
                game2.StartGame();
                resultBot2.Add(bot2.Chips);
            }
            Console.WriteLine("У второго бота остается в среденем {0} фишек.\n", resultBot2.Average());
            Console.WriteLine("Для начала игры нажмите любую клавишу.");
            Console.ReadKey();
            Console.Clear();
            var player = new Player();
            var game = new Game<Player>(player);
            game.StartGame();
        }
    }
}
