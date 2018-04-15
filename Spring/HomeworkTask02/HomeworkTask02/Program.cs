using System;
using IceCreamImplementation;

namespace HomeworkTask02
{
	static class Program
	{
		static void Main(string[] args)
		{
            IceCream iceCream = new IceCream("Ice Chocolate Cream", 0.2f, 3, IceCreamFlavor.Chocolate);
            Console.WriteLine(iceCream.GetRecipe() + "\n");

            FruitIce fruitIce = new FruitIce("Icy Raspberry", 0.3f, FruitFlavor.Raspberry);
            Console.WriteLine(fruitIce.GetRecipe() + "\n");

            WaffleCake cake = new WaffleCake("Cold Waffle Cake", IceCreamFlavor.Vanilla, 4);
            Console.WriteLine(cake.GetRecipe() + "\n");
        }
    }
}
