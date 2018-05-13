public class SmartBot extends Player {
    public SmartBot(double money){
        super("Smart Bot", money);
    }
    @Override
    public Action Play(Card dealersFirstCard) {
        if(score <= 11)
        {
            return Action.HIT;
        }
        else if((score > 17) && ((dealersFirstCard.getScore() == 9) || (dealersFirstCard.getScore() == 10)))
        {
            return Action.HIT;
        }
        else
            return Action.STAND;
    }
}
