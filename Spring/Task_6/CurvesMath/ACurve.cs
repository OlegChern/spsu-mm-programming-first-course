using System.Collections.Generic;
using System.Windows;

namespace CurvesMath
{
    public abstract class ACurve
    {
        public abstract string Name { get;}

        public abstract List<Interval> CurvesDefinedIntervals { get; protected set; }

        public abstract byte MaxNumberOfSolutions { get; }

        public abstract List<Point> FindSolutions(double x);

        public abstract void RecalculateIntervals(double DashesAmount);
    }
}