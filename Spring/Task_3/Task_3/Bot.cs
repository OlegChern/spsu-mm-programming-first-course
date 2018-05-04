namespace Task_3
{
    internal sealed class Bot : Player
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

        public int Strategy(int dealersCard)
        {
            Sum = 0;
            IsBlackjack = false;
            Hit();
            Hit();
            MakeRate(BaseRateValue);

            if ((dealersCard == 11 && Sum == 13 && Sum == 12) && IsSurrender)
            {
                return Surrender();
            }

            if (Sum == 21)
            {
                IsBlackjack = true;
                return Stand();
            }


            if ((Sum == 11 || Sum == 10) && IsDoubleDown)
            {
                return DoubleDown();
            }

            while (Sum < StopHitValue)
            {
                Hit();
            }

            return Stand();
        }
    }
}
