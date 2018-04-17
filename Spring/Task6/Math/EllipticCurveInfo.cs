using System.Collections.Generic;
using System.Linq;
using static System.Math;

namespace Math
{
    /// <summary>
    /// Class representing points of Elliptic curve
    /// y^2 = x^3 - x + 1
    /// </summary>
    public sealed class EllipticCurveInfo: CurveInfo
    {
        public override string Name => "Elliptic curve";

        internal override IEnumerable<Point> UnsafeGetPoints(Region region, double step)
        {
            var negativePoints = from point in GetPositivePoints(region, step) select new Point(point.X, -point.Y);
            return GetPositivePoints(region, step).Concat(negativePoints);
        }

        IEnumerable<Point> GetPositivePoints(Region region, double step)
        {
            double x = region.UpperLeft.X;

            while (x < region.LoweRight.X)
            {
                double valueUnderRoot = x * x * x - x + 1;

                if (valueUnderRoot < 0)
                {
                    x += step;
                    
                    continue;
                }

                double root = Sqrt(valueUnderRoot);

                yield return new Point(x, root);
                
                x += step;
            }
        }
        
    }
}
