using System;
using System.Collections.Generic;


namespace task3.Blackjack
{
    public class Dealer
    {
        private List<Card> cards;

        private int sumCards;
        public int SumCards
        {
            get
            {
                return sumCards;
            }
            private set
            {
                sumCards = value;
            }
        }

        private Card firstCard;
        public Card FirstCard
        {
            get
            {
                return firstCard;
            }
            private set
            {
                firstCard = value;
            }
        }

        public Dealer()
        {
            cards = new List<Card>();
            SumCards = 0;
        }

        private void AddCard(Decks decks)
        {
            Card card = decks.Pop();
            cards.Add(card);
            SumCards += card.GetValueOfCard();
        }

        private void AddFirstCard(Decks decks)
        {
            Card card = decks.Pop();
            cards.Add(card);
            SumCards += card.GetValueOfCard();
            FirstCard = card;
        }

        public void GiveCard(APlayer player, Decks decks)
        {
            Card card = decks.Pop();
            player.AddCard(card);
        }

        public void Dealing(List<APlayer> players, Decks decks)
        {
            for(int i = 0; i < players.Count; i++)
            {
                GiveCard(players[i], decks);
            }
            AddFirstCard(decks);

            for (int i = 0; i < players.Count; i++)
            {
                GiveCard(players[i], decks);
            }
            AddCard(decks);
        }

        public void Print()
        {
            Console.Write("Dealer: {0} cards: ", cards.Count);
            for (int i = 0; i < cards.Count - 1; i++)
            {
                cards[i].Print();
                Console.Write(", ");
            }
            cards[cards.Count - 1].Print();
        }

        public void TakeCards(Decks decks)
        {
            while(SumCards < 17)
            {
                AddCard(decks);
            }
        }

        public void ResetCards()
        {
            cards.Clear();
            SumCards = 0;
        }
    }
}
