using System;

namespace Task_2
{
    internal class AMXChasseurDeChars : Tank
    {
        public override void GetInfo()
        {
            Console.WriteLine("The characteristics of the {0}:",Name);
            Console.WriteLine("Manufacturer country: {0}", Country);
            Console.WriteLine("Weight: {0} t", Weight);
            Console.Write("Armor: ");
            Armor.WriteInfo();
            Console.WriteLine("Gun caliber: {0} mm", GunСaliber);
            Console.WriteLine("Speed limit: {0} km/h", SpeedLimit);
        }

        public AMXChasseurDeChars()
        {
            Name = "AMXChasseurDeChars";
            Country = "France";
            Weight = 34;
            Armor = new TanksArmor(30, 20, 20);
            GunСaliber = 90;
            SpeedLimit = 57;
        }
    }
}
