using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Data;
using System.Drawing;

namespace MathInfo
{
    public abstract class Curve
    {
        protected abstract double RightPart(double x);

        public abstract bool IsClosed { get; }

        public List<Point> PositivePoints { get; private set; }

        public List<Point> NegativePoints { get; private set; }

        public abstract string Name { get; }

        public override string ToString()
        {
            return Name;
        }

        public void BuildCurve(Region region, double scale)
        {
            PositivePoints = new List<Point>();
            NegativePoints = new List<Point>();
            for (int i = -region.Width / 2; i < region.Width / 2; i++)
            {
                var step = region.Width * scale / 20;
                var x = 0.01 * i / scale;
                var rightPart = RightPart(x);
                if (rightPart < 0)
                {
                    continue;
                }
                var yValue = (int)(Math.Sqrt(rightPart) * 100 * scale);
            if ((yValue > region.Height / 2) || (yValue < -region.Height / 2))
                {
                    continue;
                }
                PositivePoints.Add(new Point(i, yValue));
            }
            PositivePoints.ForEach((p) => NegativePoints.Insert(0, new Point(p.X, -p.Y)));
        }

    }
}
