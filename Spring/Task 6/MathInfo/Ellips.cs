using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MathInfo
{
    public class Ellips : Curve
    {
        public override string Name => "Эллипс"; 

        public override bool IsClosed => true;

        protected override double RightPart(double x)
        {
            return 4 - 9 * x * x / 16;
        }
    }
}
