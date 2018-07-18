using System;
using Task3.Blackjack;
using Unity;
using Unity.Injection;

namespace Task10.IoC
{
    class Program
    {
        public static IUnityContainer BlackjackContainer()
        {
            IUnityContainer container = new UnityContainer();

            container.RegisterType<APlayer, RealPlayer>("real", new InjectionConstructor("You", 1000.0));
            container.RegisterType<APlayer, BotRandom>("botRandom", new InjectionConstructor(1000.0));
            container.RegisterType<APlayer, BotDependentOnDealer>("botDependent",new InjectionConstructor(1000.0));

            container.RegisterType<Blackjack, Blackjack>("gameWithoutBot",
                new InjectionConstructor(new RealPlayer("You", 1000.0)));
            container.RegisterType<Blackjack, Blackjack>("gameWithBotRandom",
                new InjectionConstructor(new RealPlayer("You", 1000.0), new BotRandom(1000.0)));
            container.RegisterType<Blackjack, Blackjack>("gameWithBotDependent",
                new InjectionConstructor(new RealPlayer("You", 1000.0), new BotDependentOnDealer(1000.0)));

            return container;
        }

        static double CheckBot(APlayer bot)
        {
            double result = 0;
            Blackjack blackjack;
            bot.ChangeAmountOfMoney(-bot.Money);

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
            IUnityContainer container = BlackjackContainer();

            Console.WriteLine("Checking Bots:");
            Console.WriteLine("BotRandom: {0}", CheckBot(container.Resolve<APlayer>("botRandom")));
            Console.WriteLine("BotDependentOnDealer: {0}", CheckBot(container.Resolve<APlayer>("botDependent")));
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
            if (input == 1)
            {
                blackjack = container.Resolve<Blackjack>("gameWithoutBot");
            }
            else if (input == 2)
            {
                blackjack = container.Resolve<Blackjack>("gameWithBotRandom");
            }
            else
            {
                blackjack = container.Resolve<Blackjack>("gameWithBotDependent");
            }

            Console.WriteLine();
            blackjack.PrintMoney();

            bool stop = false;
            while (!stop)
            {
                blackjack.Reset();
                Console.WriteLine("\nGame on");
                blackjack.PlayBlackjack(true);
                blackjack.PrintResult();

                Console.WriteLine();
                input = -1;
                while ((input != 1) && (input != 2))
                {
                    Console.WriteLine("Continue play - 1");
                    Console.WriteLine("Stop play - 2");
                    Int32.TryParse(Console.ReadLine(), out input);
                }
                Console.WriteLine();
                if (input == 1)
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
