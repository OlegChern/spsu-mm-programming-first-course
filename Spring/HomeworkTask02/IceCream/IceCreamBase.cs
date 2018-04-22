namespace IceCreamLibrary
{
    public abstract class IceCreamBase
	{
        private string name;
        private float weight;

        public string Name
        {
            get
            {
                return name;
            }
        }

        public float Weight
        {
            get
            {
                return weight;
            }
        }

        public IceCreamBase(string name, float weight)
        {
            this.name = name;
            this.weight = weight;
        }

        public abstract string GetRecipe();
    }
}
