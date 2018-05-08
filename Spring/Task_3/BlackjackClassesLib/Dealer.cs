using System.Collections.Generic;
using System.Linq;
using BlackjackClassesLib.PlayingEvents;

namespace BlackjackClassesLib
{
    public sealed class Dealer
    {
        private List <CardsValue> DealersHand { get; }
        public CardsValue FirstCard { get; }
        public int Sum { get; private set; }
        public bool IsBlackjack { get; private set; }

        public delegate void TakingCardHandler(object sender, TakingCardEventArgs e);

        public static event TakingCardHandler CardWasTaked;
        
        public Dealer(CardsValue firstCard)
        {
            FirstCard = firstCard;
            DealersHand = new List<CardsValue> {firstCard};
            Sum = (int) firstCard;
            CardWasTaked?.Invoke(this,new TakingCardEventArgs());
        }

        public int DealersPlay(Deck gameDeck)
        {
            DealersHand.Add(gameDeck.DeckContent[gameDeck.DeckContent.Count - 1]);
            CardWasTaked?.Invoke(this, new TakingCardEventArgs());

            Sum += (int)DealersHand[DealersHand.Count - 1];

            if (Sum == 21)
            {
                IsBlackjack = true;
            }

            while (Sum <= 17)
            {
                DealersHand.Add(gameDeck.DeckContent.Last());
                CardWasTaked?.Invoke(this, new TakingCardEventArgs());

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
