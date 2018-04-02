using System;

using IceCreamLib;
using AbstractIceCreamLib;

namespace task2.AbstractClass
{
    class Program
    {
        static void Main(string[] args)
        {
            ClassicIceCream IceCreamCake = new ClassicIceCream("Ice cream cake", TypeOfIceCream.Cake, "chocolate", 3);
            Sorbet MelonSorbet = new Sorbet("Melon Sorbet", TypeOfIceCream.Cone, "melon", "strawberry");
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
