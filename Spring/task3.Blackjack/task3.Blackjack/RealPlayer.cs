using System;


namespace task3.Blackjack
{
    public class RealPlayer : APlayer
    {
        public RealPlayer(string name, double money)
            : base(name, money)
        {
        }

        public override Action Play(Dealer dealer)
        {
            Print();
            Console.WriteLine();
            Console.WriteLine("Your turn");
            int input = -1;
            bool correct = false;
            while((correct == false) || ((input != 0) && (input != 1)))
            {
                Console.WriteLine("0 - hit");
                Console.WriteLine("1 - stand");

                correct = Int32.TryParse(Console.ReadLine(), out input);
            }

            return (Action)input;
        }
    }
}
