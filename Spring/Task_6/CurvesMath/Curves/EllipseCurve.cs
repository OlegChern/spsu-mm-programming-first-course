using System;
using System.Collections.Generic;
using System.Windows;

namespace CurvesMath.Curves
{
    public class EllipseCurve : ACurve
    {
        private readonly double _sqrA;
        private readonly double _sqrB;

        public override List<Interval> CurvesDefinedIntervals { get; protected set; }
        public override byte MaxNumberOfSolutions { get; }


        public EllipseCurve(double a, double b)
        {
            _sqrA = a * a;
            _sqrB = b * b;
            CurvesDefinedIntervals = new List<Interval>{new Interval(-a,a)};
            MaxNumberOfSolutions = 2;
        }

        public override List<Point> FindSolutions(double x)
        {
            return new List<Point>
            {
                new Point(x, Math.Sqrt(_sqrB - x * x * _sqrB / _sqrA)),
                new Point(x, -Math.Sqrt(_sqrB - x * x * _sqrB / _sqrA))
            };
        }

        public override void RecalculateIntervals(double DashesAmount)
        {
        }

        public override string ToString()
        {
            return "x^2/" + _sqrA + " + y^2/" + _sqrB + " = 1";
        }

    }
    
}
