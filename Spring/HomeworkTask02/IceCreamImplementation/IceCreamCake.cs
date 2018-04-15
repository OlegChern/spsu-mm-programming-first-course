using IceCreamLibrary;

namespace IceCreamImplementation
{
    public enum WaffleCakeFlavor
    {
        Strawberry,
        Raspberry,
        Blueberry,
        Banana
    }

    public class WaffleCake : IceCreamBase
    {
        private readonly string[] waffleCakeRecipe = {
            " Put the ice cream ball on the waffle and repeat it ",
            " times." };

        private IceCream iceCream;
        private int waffleCount;

        public WaffleCake(string name, IceCreamFlavor flavor, int waffleCount) : base(name, 0.7f)
        {
            this.waffleCount = waffleCount;
            iceCream = new IceCream(string.Empty, 0.5f, waffleCount - 1, flavor);
        }

        public override string GetRecipe()
        {
            string result = iceCream.GetRecipe();
            result += waffleCakeRecipe[0] + (waffleCount - 1) + waffleCakeRecipe[1];

            return result;
        }
    }
}
