using System;
using System.Collections.Generic;
using System.Windows;

namespace CurvesMath.Curves
{
    public class HyperbolaCurve : ACurve
    {
        private readonly double _sqrA;
        private readonly double _sqrB;

        public override List<Interval> CurvesDefinedIntervals { get; protected set; }
        public override byte MaxNumberOfSolutions { get; }

        public HyperbolaCurve(double a, double b)
        {
            _sqrA = a*a;
            _sqrB = b*b;        
            MaxNumberOfSolutions = 2;
        }

        public override List<Point> FindSolutions(double x)
        {
            double y = Math.Sqrt(-_sqrB + x * x * _sqrB / _sqrA);

            if (y < 0.1)
            {
                return new List<Point> {new Point(x, 0)};
            }

            return new List<Point>
            {
                new Point(x, y),
                new Point(x, -y)
            };

        }

        public override void RecalculateIntervals(double DashesAmount)
        {
            CurvesDefinedIntervals = new List<Interval> { new Interval(-DashesAmount, -Math.Sqrt(_sqrA)), new Interval(Math.Sqrt(_sqrA), DashesAmount) };
        }

        public override string ToString()
        {
            return "x^2/" + _sqrA + " - y^2/" + _sqrB + " = 1";
        }
    }
}
