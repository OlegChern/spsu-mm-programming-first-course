namespace BlackjackClassesLib
{
    public sealed class Bot : Player
    {
        private int BaseRateValue { get; }
        private int StopHitValue { get; }
        private bool IsDoubleDown { get; }
        private bool IsSurrender { get; }

        public Bot(
                    double money, 
                    Deck gameDeck,
                    int baseRateValue, 
                    int stopHitValue, 
                    bool isDoubleDown = false,
                    bool isSurrender = false
                   ) : base(money, gameDeck)
        {
            BaseRateValue = baseRateValue;
            StopHitValue = stopHitValue;
            IsDoubleDown = isDoubleDown;
            IsSurrender = isSurrender;
        }

        public void Strategy(CardsValue dealersCard)
        {
            Sum = 0;
            IsBlackjack = false;
            Hit();
            Hit();
            MakeRate(BaseRateValue);


            if (Sum == 21)
            {
                IsBlackjack = true;
                Sum = Stand();
            }

            if (((int)dealersCard == 11 && Sum == 13 && Sum == 12) && IsSurrender)
            {
                Sum = Surrender();
            }
            


            if ((Sum == 11 || Sum == 10) && IsDoubleDown)
            {
                Sum = DoubleDown();
            }

            while (Sum < StopHitValue)
            {
                Hit();
            }

            Sum = Stand();
        }
    }
}
