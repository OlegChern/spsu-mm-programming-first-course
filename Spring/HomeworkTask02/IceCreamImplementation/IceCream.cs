using IceCreamLibrary;

namespace IceCreamImplementation
{
    public enum IceCreamFlavor
    {
        Vanilla,
        Chocolate
    }

    public class IceCream : IceCreamBase
    {
        private readonly string[] creamRecipe = {
            "Combine milk, cream, sugar, salt and ",
            " extract. Freeze the resulting mixture. Weight of 1 ball should be ",
            " kg to make ", " pieces of ", " kg." };

        private int ballCount;
        private IceCreamFlavor flavor;

        public IceCream(string name, float weight, int ballCount, IceCreamFlavor flavor) : base(name, weight)
        {
            this.flavor = flavor;
            this.ballCount = ballCount;
        }

        public override string GetRecipe()
        {
            string flavorStr = flavor.ToString();

            string result = "Recipe of " + Name + ": ";
            result += creamRecipe[0] + flavorStr + creamRecipe[1]
                + (Weight / ballCount).ToString("F") + creamRecipe[2]
                + ballCount + creamRecipe[3] + Weight + creamRecipe[4];

            return result;
        }
    }
}
