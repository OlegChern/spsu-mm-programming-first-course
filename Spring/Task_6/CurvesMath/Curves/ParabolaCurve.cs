using System;
using System.Collections.Generic;
using System.Windows;

namespace CurvesMath.Curves
{
    public class ParabolaCurve : ACurve
    {
        private readonly double _doubleCoefficientP;

        public override string Name { get; }
        public override List<Interval> CurvesDefinedIntervals { get; protected set; }
        public override byte MaxNumberOfSolutions { get; }

        public ParabolaCurve(double p)
        {
            _doubleCoefficientP = 2* p;
            Name = "y^2 =" + 2 * _doubleCoefficientP + "x";
            MaxNumberOfSolutions = 2;
        }



        public override List<Point> FindSolutions(double x)
        {
            return new List<Point>
            {
                new Point(x, Math.Sqrt(_doubleCoefficientP * x)),
                new Point(x, -Math.Sqrt(_doubleCoefficientP * x))
            };
        }

        public override void RecalculateIntervals(double DashesAmount)
        {
            CurvesDefinedIntervals = new List<Interval> { new Interval(0, DashesAmount) };
        }


        public override string ToString()
        {
            return Name;
        }
    }
}
