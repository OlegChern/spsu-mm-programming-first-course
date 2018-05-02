using System;
using System.Collections.Generic;
using System.Drawing;

namespace AlgebraicCurveLibrary.Exapmles
{
    /// <summary>
    /// y^2 = 2px
    /// </summary>
    public class Parabola : Curve
    {
        private const float DefaultParameter = 5f;

        private float parameter;

        #region constructors
        /// <summary>
        /// Creates parabola
        /// </summary>
        /// <param name="parameter">distance of the focus from the directrix</param>
        public Parabola(float parameter) : base("Parabola")
        {
            this.parameter = parameter;
        }

        /// <summary>
        /// Creates parabola with default parameters
        /// </summary>
        public Parabola() : this(DefaultParameter) { }
        #endregion

        public override PointF[][] GetDrawingPoints(Vector2 upperLeft, Vector2 lowerRight)
        {
            List<PointF> points = new List<PointF>();

            float epsilon = CalculateEpsilon(upperLeft.X);

            CalculateParabolaPoints(points, lowerRight.X, epsilon);

            PointF[][] result = new PointF[1][];
            result[0] = points.ToArray();

            return result;
        }

        private void CalculateParabolaPoints(List<PointF> list, float bound, float epsilon)
        {
            float x = Math.Abs(bound);

            // upper part
            while (x > 0)
            {
                float sqrY = 2 * parameter * x;

                if (sqrY > 0)
                {
                    float y = (float)Math.Sqrt(sqrY);
                    list.Add(new PointF(x, y));
                }

                x -= epsilon;
            }

            // lower part
            List<PointF> reversed = new List<PointF>(list);
            reversed.Reverse(0, list.Count);

            // add (0, 0)
            list.Add(new PointF(0, 0));

            // create new list with inverted y coord
            List<PointF> invertedY = new List<PointF>();
            foreach (PointF point in reversed)
            {
                invertedY.Add(new PointF(point.X, -point.Y));
            }

            list.AddRange(invertedY);
        }
    }
}
