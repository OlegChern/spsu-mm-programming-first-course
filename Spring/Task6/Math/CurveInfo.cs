using System.Collections.Generic;

namespace Math
{
    /// <summary>
    /// Class encpsulating information about curve on plane
    /// </summary>
    public abstract class CurveInfo
    {
        public abstract string Name { get; }
        
        public IEnumerable<Point> GetPoints(Region region)
        {
            double step = region.Width / 1024;

            if (step < double.Epsilon * 2)
            {
                step = double.Epsilon * 2;
            }

            return UnsafeGetPoints(region, step);
        }

        internal abstract IEnumerable<Point> UnsafeGetPoints(Region region, double step);
    }
}
