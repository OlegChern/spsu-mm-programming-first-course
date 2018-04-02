using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class FirstBot : Player
    {
        
        public FirstBot(double money, List<int> gameDeck) : base(money, gameDeck)
        {
        }


        public int FirstStrategy(int dealersCard)
        {
            IsBlackjack = false;
            IsInsurance = false;
            Hit();
            Hit();
            MakeRate(30);

            if (Sum == 21)
            {
                IsBlackjack = true;
                if (dealersCard == 11)
                {
                    MakeInsurance();
                }
                return Stand();
            }


            if (Sum == 11 && Sum == 10)
            {
                return DoubleDown();
            }

            while (true)
            {
                if (Sum >= 17)
                {
                    return Stand();
                }
                if ((dealersCard <= 6) && (Sum >= 13))
                {
                    return Stand();
                }
                Hit();
            }
            
        }
    }
}
