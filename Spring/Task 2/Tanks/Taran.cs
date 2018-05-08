using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AbstractTank;

namespace Tanks
{
    public class Taran : Tank
    {
        public double MashineGun { get; set; }   // Пулемет (мм)

        public Taran() : base("C1 Ariete \"Таран\"", "Италия", 54, 65, 4, 120, 1300)
        {
            MashineGun = 7.62;
        }

        public override void GetInfo()
        {
            base.GetInfo();
            Console.WriteLine("Пулемет: {0} мм\n", MashineGun);
        }
    }
}
