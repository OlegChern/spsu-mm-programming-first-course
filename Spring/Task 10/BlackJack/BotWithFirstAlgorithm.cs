using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class BotWithFirstAlgorithm : Bot
    {
        public override string IsNext()
        {
            if (Sum < 16)
            {
                return "Да";
            }
            return "Нет";
        }

        public override bool MakeBet()
        {
            Bet = Chips / 2;
            return true;
        }

        public override string TakeProfit()
        {
            return "Да";
        }
    }
}
