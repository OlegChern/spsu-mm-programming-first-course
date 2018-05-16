using System;
using System.Collections.Generic;
using System.Drawing;

namespace AlgebraicCurveLibrary.Exapmles
{
    /// <summary>
    /// x^2/a^2 - y^2/b^2 = 1
    /// </summary>
    public class Hyperbola : Curve
    {
        private const float DefaultA = 30f;
        private const float DefaultB = 20f;

        private float a, b;

        #region constructors
        /// <summary>
        /// Creates hyperbola
        /// </summary>
        /// <param name="a">real semi axis</param>
        /// <param name="b">imaginary semi axis</param>
        public Hyperbola(float a, float b) : base("Hyperbola")
        {
            this.a = a;
            this.b = b;
        }

        /// <summary>
        /// Creates hyperbola with default parameters
        /// </summary>
        public Hyperbola() : this(DefaultA, DefaultB) { }
        #endregion

        public override PointF[][] GetDrawingPoints(Vector2 upperLeft, Vector2 lowerRight)
        {
            List<PointF> leftPoints = new List<PointF>();
            List<PointF> rightPoints = new List<PointF>();

            float epsilon = CalculateEpsilon(upperLeft, lowerRight);

            // left part
            CalculateHyberbolaPoints(leftPoints, upperLeft.X > lowerRight.X ? upperLeft.X : lowerRight.X, -a, epsilon);

            // right part, just invert x axis
            for (int i = 0; i < leftPoints.Count; i++)
            {
                rightPoints.Add(new PointF(-leftPoints[i].X, leftPoints[i].Y));
            }

            PointF[][] result = new PointF[2][];
            result[0] = leftPoints.ToArray();
            result[1] = rightPoints.ToArray();

            return result;
        }

        private void CalculateHyberbolaPoints(List<PointF> list, float bound, float vertex, float epsilon)
        {
            float x = bound > 0 ? -bound : bound;

            // upper part
            while (Math.Abs(x) > Math.Abs(vertex))
            {
                float sqrY = (x * x / (a * a) - 1f) * b * b;

                if (sqrY > 0)
                {
                    float y = (float)Math.Sqrt(sqrY);
                    list.Add(new PointF(x, y));
                }

                x += epsilon;
            }

            // lower part
            List<PointF> reversed = new List<PointF>(list);
            reversed.Reverse(0, list.Count);

            // add (a, 0)
            list.Add(new PointF(vertex, 0));

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
