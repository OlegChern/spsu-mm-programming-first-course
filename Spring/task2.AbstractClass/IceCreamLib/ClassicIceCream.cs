using System;

using AbstractIceCreamLib;

namespace IceCreamLib
{
    public class ClassicIceCream : AbstractIceCream
    {
        private string topping;

        public string Topping
        {
            get
            {
                return topping;
            }
            private set
            {
                topping = value;
            }
        }

        private int numberOfBalls;

        public int NumberOfBalls
        {
            get
            {
                return numberOfBalls;
            }
            private set
            {
                if (value < 1)
                {
                    numberOfBalls = 1;
                }
                else if (value > 5)
                {
                    numberOfBalls = 5;
                }
                else
                {
                    numberOfBalls = value;
                }
            }
        }

        public ClassicIceCream(string name, TypeOfIceCream type, string topping, int numberOfBalls)
            : base(name, 100, type, "vanilla")
        {
            Topping = topping;
            NumberOfBalls = numberOfBalls;
        }

        public override void GetInfo()
        {
            base.GetInfo();

            Console.WriteLine("Topping: {0}", Topping);
            Console.WriteLine("NumperOfBalls: {0}", NumberOfBalls);
        }
    }
}
