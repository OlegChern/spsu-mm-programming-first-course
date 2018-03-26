using System;


namespace task3.Blackjack
{
    public class Bot1 : APlayer
    {
        public Bot1(double money)
            : base("Bot1", money)
        {
        }

        public override Action Play(Dealer dealer)
        {
            if(SumCards > 16)
            {
                return Action.stand;
            }

            Random rand = new Random();
            int result = rand.Next(1);
            return (Action)result;
        }
    }
}
