using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Bot2 : Bot
    {
        public override bool IsNext(Deck deck)
        {
            if ((Sum < 14) && (HaveAce == false))
            {
                HitMe(deck);
                return true;
            }
            else if ((Sum < 17) && (HaveAce))
            {
                HitMe(deck);
                return true;
            }
            return false;
        }

        public override void MakeBet()
        {
            Bet = 100;
        }

        public override bool TakeProfit()
        {
            return false;
        }
    }
}
