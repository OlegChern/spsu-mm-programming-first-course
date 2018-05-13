using System.Collections.Generic;
using System.Linq;

namespace BlackjackClassesLib
{
    public sealed class Dealer
    {
        private List <CardsValue> DealersHand { get; }
        public CardsValue FirstCard { get; }
        public int Sum { get; private set; }
        public bool IsBlackjack { get; private set; }

        public Dealer(CardsValue firstCard)
        {
            FirstCard = firstCard;
            DealersHand = new List<CardsValue> {firstCard};
            Sum = (int) firstCard;
        }

        public int DealersPlay(Deck gameDeck)
        {
            DealersHand.Add(gameDeck.GiveCard());

            Sum += (int)DealersHand[DealersHand.Count - 1];

            if (Sum == 21)
            {
                IsBlackjack = true;
            }

            while (Sum <= 17)
            {
                DealersHand.Add(gameDeck.GiveCard());

                Sum += (int)DealersHand[(DealersHand.Count - 1)];
                if (Sum > 21 && (DealersHand.IndexOf(CardsValue.Ace) >= 0))
                {
                    DealersHand[DealersHand.IndexOf(CardsValue.Ace)] = DealersHand[DealersHand.IndexOf(CardsValue.Ace)] - 10;
                    Sum -= 10;
                }
            }
            return Sum;
        }

        

    }
}
