using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2
{
    class AMXChasseurDeChars : Tank
    {

        public override void GetInfo()
        {
            Console.WriteLine("The characteristics of the AMXChasseurDeChars:");
            Console.WriteLine("Manufacturer country: {0}", this.Country);
            Console.WriteLine("Weight: {0} t", this.Weight);
            Console.Write("Armor: ");
            _armor.WriteInfo();
            Console.WriteLine("Gun caliber: {0} mm", this.Gun_сaliber);
            Console.WriteLine("Speed limit: {0} km/h", this.Speed_limit);
        }


        public AMXChasseurDeChars()
        {
            Country = "France";
            Weight = 34;
            _armor = new TanksArmor(30, 20, 20);
            Gun_сaliber = 90;
            Speed_limit = 57;
        }
    }
}
