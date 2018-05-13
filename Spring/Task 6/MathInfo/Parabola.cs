using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathInfo
{
    public class Parabola : Curve
    {
        public override string Name => "Парабола";

        public override bool IsClosed => false;

        protected override double RightPart(double x)
        {
            return 9 * x;
        }
    }
}
