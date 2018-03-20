using System;

using IceCreamLib;

namespace task2.AbstractClass
{
    class Program
    {
        static void Main(string[] args)
        {
            Classic IceCreamCake = new Classic("Ice cream cake", "incorrectType", "chocolate", 3);
            Sorbet MelonSorbet = new Sorbet("Melon Sorbet", "cone", "melon", "strawberry");
            FruitIce AppleIce = new FruitIce("Apple Ice", "apple");

            IceCreamCake.GetInfo();
            Console.WriteLine();
            MelonSorbet.GetInfo();
            Console.WriteLine();
            AppleIce.GetInfo();
            Console.WriteLine();
        }
    }
}
