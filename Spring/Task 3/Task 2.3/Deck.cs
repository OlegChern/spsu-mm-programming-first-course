using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Deck
    {
        public List<Card> Cards { get; set; }

        public Card GiveCard()
        {
            var card = Cards.First();
            Cards.RemoveAt(0);
            return card;
        }

        public Deck()
        {
            Cards = new List<Card>();
            Random rnd = new Random();
            for (int x = 0; x < 8; x++)
            {
                var name = new List<string>() { "2", "3", "4", "5", "6", "7", "8", "9", "10", "В", "Д", "К", "Т" };
                var suit = new List<string>() { "♠", "♣", "♥", "♦" };
                foreach (var eName in name)
                {
                    foreach (var eSuit in suit)
                    {
                        Cards.Insert(rnd.Next(0, Cards.Count), new Card(eName, eSuit));
                    }
                }
            }
        }
    }
}
