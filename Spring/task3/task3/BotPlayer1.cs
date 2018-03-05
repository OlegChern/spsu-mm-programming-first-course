using System;

namespace task3
{
    /**
     * Bot that behaves similarly to dealer:
     * taks cards as long as below 17.
     * Doesn't perform other actions.
     */
    class BotPlayer1 : AbstractPlayer
    {
        public BotPlayer1(uint initialMoney, string name = "Bot 1") : base(initialMoney, name)
        {
        }

        public override Action ChooseAction(Dealer dealer, Hand hand)
        {
            Action result;
            if (Card.GetScore(hand.Cards) < 17)
            {
                result = Action.Hit;
            }
            else
            {
                result = Action.Stand;
            }
            Console.WriteLine($"{Name} decided to {result}!");
            return result;
        }

        public override uint MakeInitialBet()
        {
            uint bet;
            if (Money >= 10)
            {
                Money -= 10;
                bet = 10;
            }
            else
            {
                Money = 0;
                bet = Money;
            }
            Console.WriteLine($"{Name} bets {bet}$ out of {Money + bet}$");
            return bet;
        }
    }
}
