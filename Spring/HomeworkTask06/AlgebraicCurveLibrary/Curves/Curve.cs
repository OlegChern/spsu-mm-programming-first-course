using System;
using System.Drawing;

namespace AlgebraicCurveLibrary
{
    public abstract class Curve : CurveBase
    {
        private const int PointsCount = 35;

        /// <summary>
        /// Creates empty curve
        /// </summary>
        /// <param name="name">name of the curve</param>
        public Curve(string name) : base(name, DrawableCurveType.Curve) { }

        /// <summary>
        /// Calculates drawing points in bounding box
        /// </summary>
        /// <param name="ul">upper left vertex of bounding box</param>
        /// <param name="lr">lower right vertex of bounding box</param>
        /// <returns></returns>
        public abstract PointF[][] GetDrawingPoints(Vector2 upperLeft, Vector2 lowerRight);

        /// <summary>
        /// Returns step for calculation
        /// </summary>
        protected float CalculateEpsilon(Vector2 upperLeft, Vector2 lowerRight)
        {
            float maxX = Math.Max(Math.Abs(upperLeft.X), Math.Abs(lowerRight.X));
            float maxY = Math.Max(Math.Abs(upperLeft.Y), Math.Abs(lowerRight.Y));

            return Math.Max(maxX, maxY) / PointsCount;
        }
    }
}
