using System;

namespace Task3
{
    class HumanPlayer : AbstractPlayer
    {
        public HumanPlayer(uint initialMoney, string name = "You") : base(initialMoney, name)
        {
        }

        public override Action ChooseAction(Dealer dealer, Hand hand)
        {
            var actions = GetPossibleActions(hand);
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
            return ChooseAction(dealer, hand);
        }

        public override uint MakeInitialBet()
        {
            Console.WriteLine("Your turn to make bet.");
            Console.WriteLine($"Your money: {Money}$.");

            do
            {
                Console.Write("Please, enter your initial bet: ");
                bool result = uint.TryParse(Console.ReadLine(), out uint initialBet);
                if (!result)
                {
                    Console.Write("Error: not a number. ");
                    continue;
                }
                if (initialBet > Money)
                {
                    Console.Write("Error: not enough money. ");
                    continue;
                }

                if (initialBet <= 0)
                {
                    Console.Write("Error: sum too small. ");
                    continue;
                }
                // Console.WriteLine($"You bet {initialBet}$");
                Money -= initialBet;
                return initialBet;
            }
            while (true);
        }
    }
}
