using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Curves
{
    /// <summary>
    /// x^2/a + y^2/b = 1
    /// </summary>
    public class Hyperbola : ACurve
    {
        public float a { get; }

        public float b { get; }

        public Hyperbola(float a = 1, float b = 1, float start = -10, float end = 10) :
            base(start, end)
        {
            Name = "Hyperbola";
            this.a = a;
            this.b = b;
            Equation = "x^2/" + a + " - y^2/" + b + " = 1";
        }

        public override List<float> FindSolutions(float x)
        {
            List<float> result = new List<float>();
            float y2 = - b + (b / a) * x * x;
            if(y2 < 0)
            {
                return result;
            }
            float y = (float)Math.Sqrt(y2);
            if (y == -y)
            {
                result.Add(y);
                return result;
            }
            else
            {
                result.Add(y);
                result.Add(-y);
                return result;
            }
        }
    }
}
