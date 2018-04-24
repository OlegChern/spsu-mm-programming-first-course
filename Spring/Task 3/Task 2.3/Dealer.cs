using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Dealer : Human
    {
        public override bool IsNext(Deck deck)
        {
            if (Sum < 17)
            {
                HitMe(deck);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
