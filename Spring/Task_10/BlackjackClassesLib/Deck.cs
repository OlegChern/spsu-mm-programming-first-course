using System;
using System.Collections.Generic;

namespace BlackjackClassesLib
{
    public class Deck
    {
        private const byte numberOfSuits = 4;

        public List<CardsValue> DeckContent { get; private set; }

        private int NumberOfDecks { get; }

        public Deck(int numberOfDecks)
        {
            NumberOfDecks = numberOfDecks;
            DeckContent = new List<CardsValue>();
        }

        public void ShuffleDeck()
        {
            List<CardsValue> temp = new List<CardsValue>();
            Random deckRandomer = new Random();

            DeckContent.Clear();
            for (int i = 0; i < NumberOfDecks * numberOfSuits; ++i)
            {
                DeckContent.Add(CardsValue.Two);
                DeckContent.Add(CardsValue.Three);
                DeckContent.Add(CardsValue.Four);
                DeckContent.Add(CardsValue.Five);
                DeckContent.Add(CardsValue.Six);
                DeckContent.Add(CardsValue.Seven);
                DeckContent.Add(CardsValue.Eight);
                DeckContent.Add(CardsValue.Nine);
                DeckContent.Add(CardsValue.Ten);
                DeckContent.Add(CardsValue.Jack);
                DeckContent.Add(CardsValue.Queen);
                DeckContent.Add(CardsValue.King);
                DeckContent.Add(CardsValue.Ace);
            }

            while (DeckContent.Count != 0)
            {
                int takenCardsPos = deckRandomer.Next(DeckContent.Count - 1);
                temp.Add(DeckContent[takenCardsPos]);
                DeckContent.RemoveAt(takenCardsPos);
            }

            DeckContent = temp;
        }

        public CardsValue GiveCard()
        {
            CardsValue result = DeckContent[DeckContent.Count - 1];
            DeckContent.RemoveAt(DeckContent.Count - 1);
            return result;
        }
    }
}
