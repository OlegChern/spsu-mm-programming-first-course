namespace task3.Blackjack
{
    public class Bot2 : APlayer
    {
        public Bot2(double money)
            : base("Bot2", money)
        {
        }

        public override Action Play(Dealer dealer)
        {
            if (SumCards > 19)
            {
                return Action.stand;
            }
            if(SumCards < 10)
            {
                return Action.hit;
            }
            if(dealer.FirstCard.GetValueOfCard() > 9)
            {
                return Action.hit;
            }
            return Action.stand;
        }
    }
}
