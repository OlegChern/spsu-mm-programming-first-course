using System;


namespace Task3.Blackjack
{
    public class RealPlayer : APlayer
    {
        public RealPlayer(string name, double money)
            : base(name, money)
        {
        }

        public override Action Play(Card dealersFirstCard)
        {
            Print();
            Console.WriteLine();
            Console.WriteLine("Your turn");
            int input = -1;
            while((input != 1) && (input != 2))
            {
                Console.WriteLine("1 - hit");
                Console.WriteLine("2 - stand");

                Int32.TryParse(Console.ReadLine(), out input);
            }

            return (Action)input;
        }
    }
}
