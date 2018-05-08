using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathInfo
{
    public class Hyperbola : Curve
    {
        public override string Name { get => "Сопряженная гипербола"; }

        protected override double RightPart(double x)
        {
            return 9 + 4 * x * x / 9;
        }
    }
}
