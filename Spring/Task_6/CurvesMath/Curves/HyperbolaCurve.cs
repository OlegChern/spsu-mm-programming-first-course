using System;
using System.Collections.Generic;
using System.Windows;

namespace CurvesMath.Curves
{
    public class HyperbolaCurve : ACurve
    {
        private readonly double _sqrCoefficientA;
        private readonly double _sqrCoefficientB;

        public override string Name { get; }
        public override List<Interval> CurvesDefinedIntervals { get; protected set; }
        public override byte MaxNumberOfSolutions { get; }

        public HyperbolaCurve(double a, double b)
        {
            _sqrCoefficientA = a*a;
            _sqrCoefficientB = b*b;
            Name = "x^2/" + _sqrCoefficientA + " - y^2/" + _sqrCoefficientB + " = 1";
            MaxNumberOfSolutions = 2;
        }

        public override List<Point> FindSolutions(double x)
        {
            double y = Math.Sqrt(-_sqrCoefficientB + x * x * _sqrCoefficientB / _sqrCoefficientA);

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
            CurvesDefinedIntervals = new List<Interval> { new Interval(-DashesAmount, -Math.Sqrt(_sqrCoefficientA)), new Interval(Math.Sqrt(_sqrCoefficientA), DashesAmount) };
        }

        public override string ToString()
        {
            return Name;
        }
    }
}
