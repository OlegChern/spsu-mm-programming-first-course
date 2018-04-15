namespace IceCreamLibrary
{
    public abstract class IceCreamBase
	{
        private string name;
        private float weight;

        protected string Name
        {
            get
            {
                return name;
            }
        }

        protected float Weight
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
