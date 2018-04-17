using System;
using System.Collections.Generic;
using System.Linq;
using static System.Math;

namespace Math
{
    /// <summary>
    /// Class representing points of circle
    /// x^2 + y^2 = Radius^2
    /// </summary>
    sealed class CentralCircleInfo : CurveInfo
    {
        public override string Name => "Circle";
        
        double Radius { get; }

        public CentralCircleInfo(double radius)
        {
            if (radius <= 0)
            {
                throw new ArgumentException(
                    $"{nameof(radius)} ({radius}) is not positive and cannot be treated as circle radius");
            }

            Radius = radius;
        }

        internal override IEnumerable<Point> UnsafeGetPoints(Region region, double step)
        {
            var negativePoints = from point in GetPositivePoints(region, step) select new Point(point.X, -point.Y);
            return GetPositivePoints(region, step).Concat(negativePoints);
        }

        IEnumerable<Point> GetPositivePoints(Region region, double step)
        {
            double x = region.UpperLeft.X;

            double squareRadius = Radius * Radius;

            while (x < region.LoweRight.X)
            {
                double valueUnderRoot = squareRadius - x * x;

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
