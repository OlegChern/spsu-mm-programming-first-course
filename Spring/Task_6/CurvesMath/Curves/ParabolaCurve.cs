using System;
using System.Collections.Generic;
using System.Windows;

namespace CurvesMath.Curves
{
    public class ParabolaCurve : ACurve
    {
        private readonly double _2p;

        public override List<Interval> CurvesDefinedIntervals { get; protected set; }
        public override byte MaxNumberOfSolutions { get; }

        public ParabolaCurve(double p)
        {
            _2p = 2 * p;
            MaxNumberOfSolutions = 2;
        }



        public override List<Point> FindSolutions(double x)
        {
            return new List<Point>
            {
                new Point(x, Math.Sqrt(_2p * x)),
                new Point(x, -Math.Sqrt(_2p * x))
            };
        }

        public override void RecalculateIntervals(double DashesAmount)
        {
            CurvesDefinedIntervals = new List<Interval> { new Interval(0, DashesAmount) };
        }


        public override string ToString()
        {
            return "y^2 =" + _2p + "x";
        }
    }
}
