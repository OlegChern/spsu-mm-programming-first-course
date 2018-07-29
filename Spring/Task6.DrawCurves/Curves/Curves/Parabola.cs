using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Curves
{
    /// <summary>
    /// y = px
    /// </summary>
    public class Parabola : ACurve
    {
        public float p { get; }

        public Parabola(float p = 1, float start = -10, float end = 10) :
            base(start, end)
        {
            Name = "Parabola";
            this.p = p;
            Equation = "y^2 = " + p + "x";
        }

        public override List<float> FindSolutions(float x)
        {
            List<float> result = new List<float>();
            float y2 = p * x;
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
