using System;

using IceCreamLibrary;
using IceCreamImplementation;

namespace HomeworkTask02
{
	static class Program
	{
		static void Main(string[] args)
		{
            IceCreamBase iceCream = new IceCream("Ice Chocolate Cream", 0.2f, 3, IceCreamFlavor.Chocolate);
            IceCreamBase fruitIce = new FruitIce("Icy Raspberry", 0.3f, FruitFlavor.Raspberry);
            IceCreamBase cake = new WaffleCake("Cold Waffle Cake", IceCreamFlavor.Vanilla, 4);

            PrintInfo(iceCream);
            PrintInfo(fruitIce);
            PrintInfo(cake);
        }

        static void PrintInfo(IceCreamBase product)
        {
            Console.WriteLine("Recipe of " + product.Name + " weighing " + product.Weight + " kg: ");
            Console.WriteLine(product.GetRecipe() + "\n");
        }
    }
}
