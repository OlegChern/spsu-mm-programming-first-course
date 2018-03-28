using System;

using AbstractIceCreamLib;

namespace IceCreamLib
{
    public class Sorbet : AbstractIceCream
    {
        private string syrup;

        public string Syrup
        {
            get
            {
                return syrup;
            }
            set
            {
                syrup = value;
            }
        }

        public Sorbet(string name, TypeOfIceCream type, string flavor, string syrup)
            : base(name, 70, type, flavor)
        {
            Syrup = syrup;
        }

        public override void GetInfo()
        {
            base.GetInfo();
            Console.WriteLine("Syrup: {0}", Syrup);
        }
    }
}
