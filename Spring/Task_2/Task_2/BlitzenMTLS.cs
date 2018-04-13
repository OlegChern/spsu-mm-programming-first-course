using System;

namespace Task_2
{
    internal sealed class BlitzenMTLS : Tank
    {
        public override void GetInfo()
        {
            Console.WriteLine("The characteristics of the {0}:", Name);
            Console.WriteLine("Manufacturer country: {0}", Country);
            Console.WriteLine("Weight: {0} t", Weight);
            Console.Write("Armor: ");
            Armor.WriteInfo();
            Console.WriteLine("Gun caliber: {0} mm", GunСaliber);
            Console.WriteLine("Speed limit: {0} km/h", SpeedLimit);
            Console.WriteLine();
        }

        public BlitzenMTLS()
        {
            Name = "BlitzenMTLS";
            Country = "USA";
            Weight = 15.47;
            Armor = new TanksArmor(38,25,25);
            GunСaliber = 37;
            SpeedLimit = 42;
        }
    }
}
