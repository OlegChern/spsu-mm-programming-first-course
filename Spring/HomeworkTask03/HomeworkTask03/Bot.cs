using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BlackJack
{
    class Bot : Player
    {
        public Bot(Game game, int startMoney) : base(game, startMoney) { }

        protected override void MakeDecision()
        {
            if (CardsSum > 0)
            {

            }
        }
    }
}
