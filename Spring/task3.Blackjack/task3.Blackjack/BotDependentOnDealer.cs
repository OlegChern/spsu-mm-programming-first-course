namespace Task3.Blackjack
{
    public class Bot2 : APlayer
    {
        public Bot2(double money)
            : base("BotDependentOnDealer", money)
        {
        }

        public override Action Play(Card dealersFirstCard)
        {
            if (SumCards > 17)
            {
                return Action.stand;
            }
            if(SumCards < 10)
            {
                return Action.hit;
            }
            if(dealersFirstCard.GetValueOfCard() > 9)
            {
                return Action.hit;
            }
            return Action.stand;
        }
    }
}
