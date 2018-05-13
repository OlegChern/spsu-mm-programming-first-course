public class LikeDealerBot extends Player {
    public LikeDealerBot(double money){
        super("Like Dealer Bot", money);
    }
    @Override
    public Action Play(Card dealersFirstCard) {
        if(score < 17)
        {
            return Action.HIT;
        }
        else
            return Action.STAND;
    }
}
