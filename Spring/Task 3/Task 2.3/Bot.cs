using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public abstract class Bot : Human, IPlayer
    {
        public override bool IsBot => true;

        public Bot() : base()
        {
            Chips = 1000;
        }

        public abstract bool MakeBet();

        public abstract string TakeProfit();       
    }
}
