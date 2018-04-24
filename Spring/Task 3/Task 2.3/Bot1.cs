using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Bot1 : Bot
    {
        public override bool IsNext(Deck deck)
        {
            if (Sum < 16)
            {
                HitMe(deck);
                return true;
            }
            return false;
        }

        public override void MakeBet()
        {
            Bet = Chips / 2;
        }

        public override bool TakeProfit()
        {
            return true;
        }
    }
}
