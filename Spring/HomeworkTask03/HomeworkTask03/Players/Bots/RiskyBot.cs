namespace BlackJack
{
    class RiskyBot : Player
    {
        public RiskyBot(int startMoney) : base(startMoney, "RiskyBot") { }

        protected override Decision MakeDecision()
        {
            if (CardsSum >= 19)
            {
                return Decision.Stand;
            }

            return Decision.Hit;
        }

        protected override int CalculateBet()
        {
            return Money;
        }
    }
}
