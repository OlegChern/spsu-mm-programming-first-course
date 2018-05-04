using System;

namespace Task_3
{
    class Program
    {
        static void Main(string[] args)
        {
            double sum1 = 0;
            double sum2 = 0;

            Game thisGame = new Game(8);
            Bot firstPlayer = new Bot(500, thisGame.GameDeck,30,17,true,false);
            Bot secondPlayer = new Bot(500, thisGame.GameDeck,25,16,false,true);


            for (int i = 0; i < 40; ++i)
            {
                thisGame.PlayGame(thisGame.GameDeck, firstPlayer, secondPlayer);
                sum2 += secondPlayer.Money;
                sum1 += firstPlayer.Money;
            }

            Console.WriteLine(sum1/40);
            Console.WriteLine(sum2/40);
        }
    }
}
