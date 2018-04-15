namespace BlackJack
{
    class FearfulBot : Player
    {
        public FearfulBot(int startMoney) : base(startMoney, "FearfulBot") { }

        protected override Decision MakeDecision()
        {
            if (CardsSum > 11)
            {
                return Decision.Stand;
            }

            return Decision.Hit;
        }
    }
}
