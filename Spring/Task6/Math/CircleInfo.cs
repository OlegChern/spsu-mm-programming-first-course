using System;
using System.Collections.Generic;
using System.Linq;

namespace Math
{
    public class CircleInfo : CurveInfo
    {
        public override string Name => "Circle";
#if DEBUG
        readonly CurveInfo centralCircle;
        readonly Point center;
#else
        CurveInfo centralCircle;
        Point center;
#endif
        

        public CircleInfo(double radius, double centerY, double centerX) : this(radius, new Point(centerX, centerY))
        {
        }

        public CircleInfo(double radius, Point center)
        {
            if (radius <= 0)
            {
                throw new ArgumentException(
                    $"{nameof(radius)} ({radius}) is not positive and cannot be treated as circle radius");
            }

            centralCircle = new CentralCircleInfo(radius);

            this.center = center;
        }


        internal override IEnumerable<Point> UnsafeGetPoints(Region region, double step)
        {
            return from point in centralCircle.UnsafeGetPoints(region, step)
                select new Point(point.X + center.X, point.Y + center.Y);
        }
    }
}

