using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2
{
    class BlitzenMTLS : Tank
    {

        public override void GetInfo()
        {
            Console.WriteLine("The characteristics of the BlitzenMTLS:");
            Console.WriteLine("Manufacturer country: {0}", this.Country);
            Console.WriteLine("Weight: {0} t", this.Weight);
            Console.Write("Armor: ");
            _armor.WriteInfo();
            Console.WriteLine("Gun caliber: {0} mm", this.Gun_сaliber);
            Console.WriteLine("Speed limit: {0} km/h", this.Speed_limit);
            Console.WriteLine();
        }


        public BlitzenMTLS()
        {
            Country = "USA";
            Weight = 15.47;
            _armor = new TanksArmor(38,25,25);
            Gun_сaliber = 37;
            Speed_limit = 42;
        }
    }
}
