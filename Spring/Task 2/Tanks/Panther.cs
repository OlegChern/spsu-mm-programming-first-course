using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AbstractTank;

namespace Tanks
{
    public class Panther : Tank
    {
        public double FirstMashineGun { get; set; }   // Первый пулемет (мм)

        public double SecondMashineGun { get; set; }   // Второй пулемет (мм)

        public Panther() : base("K2 Black Panther", "Южная корея", 55, 70, 3, 120, 1500)
        {
            FirstMashineGun = 7.62;
            SecondMashineGun = 12.7;
        }

        public override void GetInfo()
        {
            base.GetInfo();
            Console.WriteLine("Первый пулемет: {0} мм", FirstMashineGun);
            Console.WriteLine("Второй пулемет: {0} мм\n", SecondMashineGun);
        }
    }
}
