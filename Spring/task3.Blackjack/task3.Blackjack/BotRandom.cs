using System;


namespace Task3.Blackjack
{
    public class Bot1 : APlayer
    {
        public Bot1(double money)
            : base("BotRandom", money)
        {
        }

        public override Action Play(Card dealersFirstCard)
        {
            if(SumCards > 16)
            {
                return Action.Stand;
            }

            Random rand = new Random();
            int result = rand.Next(1);
            return (Action)result;
        }
    }
}
