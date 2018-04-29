namespace AlgebraicCurveLibrary
{
    public class Line : CurveBase
    {
        private static readonly Vector2 DefaultDirection = new Vector2(1f, 1f);

        private Vector2 direction;

        public Vector2 Direction
        {
            get
            {
                return direction;
            }
        }

        /// <summary>
        /// Creates line with direction vector
        /// </summary>
        /// <param name="name">name of the line</param>
        /// <param name="dir">direction vector</param>
        public Line(string name, Vector2 dir) : base(name, DrawableCurveType.Line)
        {
            dir.Normalize();
            direction = dir;
        }

        /// <summary>
        /// Creates line with two points
        /// </summary>
        /// <param name="name">name of the line</param>
        /// <param name="a">first point</param>
        /// <param name="b">second point</param>
        public Line(string name, Vector2 a, Vector2 b) : this(name, b - a) { }

        /// <summary>
        /// Creates line with default parameters
        /// </summary>
        public Line() : this("Line", DefaultDirection) { }
    }
}
