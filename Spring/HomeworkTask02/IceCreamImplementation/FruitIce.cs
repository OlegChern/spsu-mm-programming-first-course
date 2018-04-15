using IceCreamLibrary;

namespace IceCreamImplementation
{
    public enum FruitFlavor
    {
        Strawberry,
        Raspberry,
        Blueberry,
        Banana
    }

    public class FruitIce: IceCreamBase
    {
        private readonly string[] iceRecipe = {
            "Combine the sugar and water and make the syrup. Add the ",
            " juice and then allow the mixture to freeze for at least 6 hours. To make ",
            " kg of fruit ice you need about ", " litres of water." };

        private FruitFlavor flavor;

        public FruitIce(string name, float weight, FruitFlavor flavor) : base(name, weight)
        {
            this.flavor = flavor;
        }

        public override string GetRecipe()
        {
            string flavorStr = flavor.ToString();

            string result = "Recipe of " + Name + ": ";
            result += iceRecipe[0] + flavorStr + iceRecipe[1]
                + Weight + iceRecipe[2] + (Weight * 1.1f).ToString("F") + iceRecipe[3];

            return result;
        }
}
}
