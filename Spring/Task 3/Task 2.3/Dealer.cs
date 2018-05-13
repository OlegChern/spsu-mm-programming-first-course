using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public class Dealer : Human
    {
        public override bool IsBot => true;

        public override string IsNext()
        {
            if (Sum < 17)
            {
                return "Да";
            }
            else
            {
                return "Нет";
            }
        }
    }
}
