using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class BotWithSecondAlgorithm : Bot
    {
        public override string IsNext()
        {
            if ((Sum < 14) && (HaveAce == false))
            {
                return "Да";
            }
            else if ((Sum < 17) && (HaveAce))
            {
                return "Да";
            }
            return "Нет";
        }

        public override bool MakeBet()
        {
            Bet = 100;
            return true;
        }

        public override string TakeProfit()
        {
            return "Нет";
        }
    }
}
