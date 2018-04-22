namespace BlackJack
{
    class SmartBot : Player
    {
        public SmartBot(int startMoney) : base(startMoney, "SmartBot") { }

        protected override Decision MakeDecision()
        {
            if (CardsSum >= 17)
            {
                return Decision.Stand;
            }

            int dealerCardValue = Game.Dealer.FaceUpCardValue;

            if (CardsSum == 16 && dealerCardValue >= 9 && dealerCardValue <= 11)
            {
                return Decision.Surrender;
            }

            if (((CardsSum >= 13 && dealerCardValue >= 2) || (CardsSum == 12 && dealerCardValue >= 4)) && dealerCardValue <= 6)
            {
                return Decision.Stand;
            }

            if (CardsSum == 11 || CardsSum == 10 || (CardsSum == 9 && dealerCardValue >= 3 && dealerCardValue <= 6))
            {
                if (Money >= Bet * 2)
                {
                    return Decision.DoubleDown;
                }
            }

            return Decision.Hit;
        }

        protected override int CalculateBet()
        {
            return (int)(Money * 0.4f);
        }
    }
}
