using System.Linq;

namespace Math
{
    public abstract class Painter
    {
        protected const int PointSize = 3;

        protected abstract double ScreenWidth { get; }
        protected abstract double ScreenHeight { get; }

        public void Paint(CurveInfo curve, int pixelsInUnit)
        {
            Clear();

            PaintAxes();

            if (curve is null)
            {
                return;
            }

            var zeroPoint = new Point(ScreenHeight / 2, ScreenWidth / 2);

            var upperLeft = new Point(-ScreenWidth / 2, -ScreenHeight / 2) / pixelsInUnit;

            var lowerRight = new Point(ScreenWidth / 2, ScreenHeight / 2) / pixelsInUnit;

            var region = new Region(upperLeft, lowerRight);

            var realPoints =
                from point in curve.GetPoints(region)
                let realPoint = new Point(point.Y, point.X) * pixelsInUnit + zeroPoint
                // TODO: move this filtering closer to point rendering
                where realPoint.X >= 0
                      && realPoint.X <= ScreenHeight
                      && realPoint.Y >= 0
                      && realPoint.Y <= ScreenWidth
                select realPoint;

            realPoints.ForEach(point => PaintDot(point));
        }

        protected abstract void Clear();

        protected abstract void PaintAxes();

        protected abstract void PaintDot(Point dot);
    }
}
