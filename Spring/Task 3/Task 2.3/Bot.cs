using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    public abstract class Bot : Human, IPlayer
    {
        public int CountParty { get; set; }
        public Bot() : base()
        {
            CountParty = 0;
            Chips = 1024;
        }
        public abstract void MakeBet();
        public abstract bool TakeProfit();       
    }
}
