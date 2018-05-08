using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AbstractTank;
using Tanks;

namespace Program
{
    class Program
    {
        static void Main(string[] args)
        {
            var armata = new Armata();
            Console.WriteLine("Информация об первом экземпляре танка:");
            armata.GetInfo();

            var taran = new Taran();
            Console.WriteLine("Информация об втором экземпляре танка:");
            taran.GetInfo();

            var panther = new Panther();
            Console.WriteLine("Информация об третьем экземпляре танка:");
            panther.GetInfo();
        }
    }
}
