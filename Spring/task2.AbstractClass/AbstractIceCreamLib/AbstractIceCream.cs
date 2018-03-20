using System;

namespace AbstractIceCreamLib
{
    public abstract class AbstractIceCream
    {
        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            private set
            {
                name = value;
            }
        }

        private int weight; // grams
        public int Weight
        {
            get
            {
                return weight;
            }
            private set
            {
                if(value < 20)
                {
                    weight = 20;
                }
                else if(value > 400)
                {
                    weight = 400;
                }
                else
                {
                    weight = value;
                }
            }
        }

        enum TypeOfIceCream { eskimo , cone, cake};
        private TypeOfIceCream type;
        public string Type
        {
            get
            {
                return type.ToString();
            }
            private set
            {
                if (value == "eskimo" || value == "cone" || value == "cake")
                {
                    type = (TypeOfIceCream)Enum.Parse(typeof(TypeOfIceCream), value);
                }
                else
                {
                    type = TypeOfIceCream.cake;
                }
            }
        }

        private string flavor;
        public string Flavor
        {
            get
            {
                return flavor;
            }
            set
            {
                flavor = value;
            }
        }

        public AbstractIceCream(string name, int weight, string type, string flavor)
        {
            Name = name;
            Weight = weight;
            Type = type;
            Flavor = flavor;
        }

        public virtual void GetInfo()
        {
            Console.WriteLine("Name: {0}", Name);
            Console.WriteLine("Weight: {0} grams", Weight);
            Console.WriteLine("Type: {0}", Type);
            Console.WriteLine("Flavor: {0}", Flavor);
        }
    }
}
