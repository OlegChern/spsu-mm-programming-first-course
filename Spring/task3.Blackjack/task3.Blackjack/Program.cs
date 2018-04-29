using System;


namespace Task3.Blackjack
{
    class Program
    {
        static double CheckBot(APlayer bot)
        {
            double result = 0;
            Blackjack blackjack;

            for (int i = 0; i < 100; i++)
            {
                blackjack = new Blackjack(bot, null);
                for (int j = 0; j < 40; j++)
                {
                    blackjack.PlayBlackjack(false);
                    blackjack.Reset();
                }
                result += bot.Money;
                bot.ChangeAmountOfMoney(-bot.Money);
            }

            return result / 100;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Checking Bots:");
            Console.WriteLine("BotRandom: {0}", CheckBot(new BotRandom(0)));
            Console.WriteLine("BotDependentOnDealer: {0}", CheckBot(new BotDependentOnDealer(0)));
            Console.WriteLine();

            int input = -1;
            while ((input != 1) && (input != 2) && (input != 3))
            {
                Console.WriteLine("1 - play without bot");
                Console.WriteLine("2 - play with botRandom");
                Console.WriteLine("3 - play with botDependentOnDealer");

                Int32.TryParse(Console.ReadLine(), out input);
            }

            Blackjack blackjack;
            RealPlayer realPlayer = new RealPlayer("You", 1000);
            if (input == 1)
            {
                blackjack = new Blackjack(realPlayer, null);
            }
            else if(input == 2)
            {
                blackjack = new Blackjack(realPlayer, new BotRandom(1000));
            }
            else
            {
                blackjack = new Blackjack(realPlayer, new BotDependentOnDealer(1000));
            }

            Console.WriteLine();
            blackjack.PrintMoney();

            bool stop = false;
            while (!stop)
            {
                blackjack.Reset();
                Console.WriteLine("Game on");
                blackjack.PlayBlackjack(true);
                blackjack.PrintResult();

                Console.WriteLine();
                input = -1;
                while((input != 1) && (input != 2))
                {
                    Console.WriteLine("Continue play - 1");
                    Console.WriteLine("Stop play - 2");
                    Int32.TryParse(Console.ReadLine(), out input);
                }
                Console.WriteLine();
                if(input == 1)
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
            blackjack.PrintMoney();
        }
    }
}
