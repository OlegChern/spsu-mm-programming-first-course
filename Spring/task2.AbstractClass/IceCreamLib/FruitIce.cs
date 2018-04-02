using System;

using AbstractIceCreamLib;

namespace IceCreamLib
{
    public class FruitIce : AbstractIceCream
    {
        public FruitIce(string name, string flavor)
            : base(name, 60, TypeOfIceCream.Eskimo, flavor)
        {}
    }
}
