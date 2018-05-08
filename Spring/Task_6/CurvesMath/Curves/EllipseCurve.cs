using System;
using System.Collections.Generic;
using System.Windows;

namespace CurvesMath.Curves
{
    public class EllipseCurve : ACurve
    {
        private readonly double _sqrCoefficientA;
        private readonly double _sqrCoefficientB;

        public override string Name { get; }
        public override List<Interval> CurvesDefinedIntervals { get; protected set; }
        public override byte MaxNumberOfSolutions { get; }


        public EllipseCurve(double a, double b)
        {
            _sqrCoefficientA = a * a;
            _sqrCoefficientB = b * b;
            Name = "x^2/" + _sqrCoefficientA + " + y^2/" + _sqrCoefficientB + " = 1";
            CurvesDefinedIntervals = new List<Interval>{new Interval(-a,a)};
            MaxNumberOfSolutions = 2;
        }

        public override List<Point> FindSolutions(double x)
        {
            return new List<Point>
            {
                new Point(x, Math.Sqrt(_sqrCoefficientB - x * x * _sqrCoefficientB / _sqrCoefficientA)),
                new Point(x, -Math.Sqrt(_sqrCoefficientB - x * x * _sqrCoefficientB / _sqrCoefficientA))
            };
        }

        public override void RecalculateIntervals(double DashesAmount)
        {
        }

        public override string ToString()
        {
            return Name;
        }

    }
    
}
