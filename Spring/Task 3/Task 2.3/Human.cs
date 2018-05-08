using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public abstract class Human
    {
        public bool IsBot { get; set; }

        public int CountParty { get; set; }

        public List<Card> Cards { get; set; }

        public bool HaveAce { get; set; }

        public int Bet { get; set; }

        public int Chips { get; set; }

        public int Sum
        {
            get
            {
                var sum = 0;
                foreach (var e in Cards)
                {
                    sum += e.Value;
                }
                if ((HaveAce == true) && (sum > 21))
                {
                    return sum - 10;
                }
                else 
                {
                    return sum;
                }
              
            }
        }

        public Human()
        {
            Cards = new List<Card>();
            HaveAce = false;
            CountParty = 0;
        }

        public void Print()
        {
            foreach (var e in Cards)
            {
                e.Print();
            }
        }

        public void HitMe(Deck deck)
        {
            var card = deck.GiveCard();
            Cards.Add(card);
            if (card.Name == "Т")
            {
                HaveAce = true;
            }
        }

        public abstract string IsNext();
    }
}
