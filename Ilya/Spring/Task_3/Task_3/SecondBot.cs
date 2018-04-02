using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_3
{
    class SecondBot : Player
    {
        public bool IsBlackjack { get; set; }

        public SecondBot(double money, List<int> gameDeck) : base(money, gameDeck)
        {
        }


        public int SecondStrategy()
        {
            IsBlackjack = false;
            Hit();
            Hit();
            MakeRate(30);

            if (Sum == 21)
            {
                IsBlackjack = true;
                return Stand();
            }




            return 0;
        }

    }
}
