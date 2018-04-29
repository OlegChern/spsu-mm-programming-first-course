using System;


namespace Task3.Blackjack
{
    public class BotRandom : APlayer
    {
        public BotRandom(double money)
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
