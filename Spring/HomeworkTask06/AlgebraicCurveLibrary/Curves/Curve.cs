using System.Drawing;

namespace AlgebraicCurveLibrary
{
    public abstract class Curve : CurveBase
    {
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
        /// <param name="epsilon">computational error</param>
        /// <returns></returns>
        public abstract PointF[][] GetDrawingPoints(Vector2 upperLeft, Vector2 lowerRight, float epsilon);
    }
}
