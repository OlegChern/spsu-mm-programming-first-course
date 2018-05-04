using System.Collections.Generic;
using System.Linq;

namespace Task_3
{
    internal sealed class Dealer
    {
        private List <CardsValue> DealersHand { get; }
        private int Sum { get; set; }
        public bool IsBlackjack { get; }

        public Dealer(Deck gameDeck)
        {
            DealersHand = new List<CardsValue>
            {
                gameDeck.DeckContent.Last()
            };
            gameDeck.DeckContent.RemoveAt(gameDeck.DeckContent.Count -1);
            Sum += (int)DealersHand[DealersHand.Count - 1];

            DealersHand.Add(gameDeck.DeckContent[gameDeck.DeckContent.Count - 1]);
            gameDeck.DeckContent.RemoveAt(gameDeck.DeckContent.Count - 1);
            Sum += (int)DealersHand[DealersHand.Count - 1];

            if (Sum == 21)
            {
                IsBlackjack = true;
            }
        }

        public int DealersPlay(Deck gameDeck)
        {
            while (Sum <= 17)
            {
                DealersHand.Add(gameDeck.DeckContent.Last());
                gameDeck.DeckContent.RemoveAt(gameDeck.DeckContent.Count - 1);
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
