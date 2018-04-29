namespace AlgebraicCurveLibrary
{
    public class Ellipse : CurveBase
    {
        private static readonly Vector2 DefaultBoundingBox = new Vector2(300f, 200f);

        private Vector2 boundingBox;

        public float SemiMajorAxis
        {
            get
            {
                return boundingBox.X;
            }
        }

        public float SemiMinorAxis
        {
            get
            {
                return boundingBox.Y;
            }
        }

        /// <summary>
        /// Creates ellipse
        /// </summary>
        /// <param name="name">name of the ellipse</param>
        /// <param name="a">semi-major axis</param>
        /// <param name="b">semi-minor axis</param>
        public Ellipse(string name, float a, float b) : base(name, DrawableCurveType.Ellipse)
        {
            boundingBox = new Vector2(a, b);
        }

        /// <summary>
        /// Creates ellipse with bounding box
        /// </summary>
        /// <param name="name">name of the ellipse</param>
        /// <param name="box">upper right vertex of bounding box</param>
        public Ellipse(string name, Vector2 box) : base(name, DrawableCurveType.Ellipse)
        {
            boundingBox = box;
        }

        /// <summary>
        /// Creates ellipse with default parameters
        /// </summary>
        public Ellipse() : this("Ellipse", DefaultBoundingBox) { }
    }
}
