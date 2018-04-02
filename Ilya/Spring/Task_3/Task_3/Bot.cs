using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class Bot : Player
    {
        public Bot(double money, List<int> gameDeck) : base(money, gameDeck)
        {
        }



        public int FirstStrategy(int dealersCard)
        {
            Sum = 0;
            IsBlackjack = false;
            Hit();
            Hit();
            MakeRate(30);

            if (Sum == 21)
            {
                IsBlackjack = true;
                return Stand();
            }


            if (Sum == 11 || Sum == 10)
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

        public int SecondStrategy(int dealersCard)
        {
            Sum = 0;
            IsBlackjack = false;
            Hit();
            Hit();
            MakeRate(25);
            if (dealersCard == 11 && Sum == 13 && Sum == 12)
            {
                return Surrender();
            }


            if (Sum == 21)
            {
                IsBlackjack = true;
                return Stand();
            }


            if (Sum == 11 || Sum == 10 || Sum == 9)
            {
                return DoubleDown();
            }

            while (true)
            {
                if (Sum >= 16)
                {
                    return Stand();
                }

                if ((dealersCard <= 5) && (Sum >= 13))
                {
                    return Stand();
                }
                

                Hit();
            }

        }

    }
}
