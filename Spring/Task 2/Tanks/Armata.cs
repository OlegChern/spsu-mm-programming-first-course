using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AbstractTank;

namespace Tanks
{
    public class Armata : Tank
    {
        public Armata() : base("T-14 \"Армата\"", "Россия", 55, 75, 3, 125, 1500)
        {
 
        }

        public override void GetInfo()
        {
            base.GetInfo();
            Console.WriteLine();
        }
    }
}
