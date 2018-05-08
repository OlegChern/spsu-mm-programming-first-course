using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public abstract class Bot : Human, IPlayer
    {
        public Bot() : base()
        {
            Chips = 1000;
            IsBot = true;
        }

        public abstract bool MakeBet();

        public abstract string TakeProfit();       
    }
}
