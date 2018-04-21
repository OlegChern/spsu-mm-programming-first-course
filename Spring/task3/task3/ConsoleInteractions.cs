using System;
using System.Collections.Generic;

namespace Task3
{
    public static class ConsoleInteractions
    {
        public static bool Confirm(string message)
        {
            Console.Write(message);
            string s = Console.ReadLine() ?? throw new NullReferenceException();
            switch (s[0])
            {
                case 'Y':
                case 'y':
                    return true;
                case 'N':
                case 'n':
                    return false;
                default:
                    Console.Write("Error. ");
                    return Confirm(message);
            }
        }

        public static Action ChooseAction(List<Action> actions)
        {
            Console.WriteLine("Possible actions:");
            for (int i = 0; i < actions.Count; i++)
            {
                Console.Write(actions[i]);
                if (i != actions.Count - 1)
                {
                    Console.Write(", ");
                }
                else
                {
                    Console.WriteLine();
                }
            }

            Console.WriteLine("Please, choose action.");
            string input = Console.ReadLine();
            if (!int.TryParse(input, out int _)
                && Enum.TryParse<Action>(input, true, out var humanChoice)
                && actions.Contains(humanChoice))
            {
                return humanChoice;
            }

            Console.Write("Error. ");

            return ChooseAction(actions);
        }

        public static uint MakeInitialBet(uint money)
        {
            Console.WriteLine("Your turn to make bet.");
            Console.WriteLine($"Your money: {money}$.");

            do
            {
                Console.Write("Please, enter your initial bet: ");
                bool result = uint.TryParse(Console.ReadLine(), out uint initialBet);
                if (!result)
                {
                    Console.Write("Error: not a number. ");
                    continue;
                }

                if (initialBet > money)
                {
                    Console.Write("Error: not enough money. ");
                    continue;
                }

                if (initialBet <= 0)
                {
                    Console.Write("Error: sum too small. ");
                    continue;
                }

                return initialBet;
            }
            while (true);
        }
    }
}
