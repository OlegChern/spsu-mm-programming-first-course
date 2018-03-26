using System;


namespace task3.Blackjack
{
    class Program
    {
        static double CheckBot(APlayer bot)
        {
            double result = 0;
            Play play;

            for (int i = 0; i < 100; i++)
            {
                play = new Play(bot, null);
                for (int j = 0; j < 40; j++)
                {
                    play.PlayBlackjack(false);
                    play.Reset();
                }
                result += bot.Money;
                bot.ChangeAmountOfMoney(-bot.Money);
            }

            return result / 100;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Checking Bots:");
            Console.WriteLine("Bot1: {0}", CheckBot(new Bot1(0)));
            Console.WriteLine("Bot2: {0}", CheckBot(new Bot2(0)));
            Console.WriteLine();

            int input = -1;
            bool correct = false;
            while ((correct == false) || ((input != 0) && (input != 1) && (input != 2)))
            {
                Console.WriteLine("0 - play without bot");
                Console.WriteLine("1 - play with bot1");
                Console.WriteLine("2 - play with bot2");

                correct = int.TryParse(Console.ReadLine(), out input);
            }

            Play play;
            RealPlayer realPlayer = new RealPlayer("You", 1000);
            if (input == 0)
            {
                play = new Play(realPlayer, null);
            }
            else if(input == 1)
            {
                play = new Play(realPlayer, new Bot1(1000));
            }
            else
            {
                play = new Play(realPlayer, new Bot2(1000));
            }

            Console.WriteLine();
            play.PrintMoney();

            bool stop = false;
            while (!stop)
            {
                play.Reset();
                Console.WriteLine("Game on");
                play.PlayBlackjack(true);
                play.PrintResult();

                Console.WriteLine();
                input = -1;
                correct = false;
                while((correct == false) || ((input != 0) && (input != 1)))
                {
                    Console.WriteLine("Continue play - 0");
                    Console.WriteLine("Stop play - 1");
                    correct = Int32.TryParse(Console.ReadLine(), out input);
                }
                Console.WriteLine();
                if(input == 0)
                {
                    stop = false;
                }
                else
                {
                    stop = true;
                }
            }

            Console.WriteLine();
            Console.WriteLine("Results:");
            play.PrintMoney();
        }
    }
}
