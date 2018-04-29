namespace AlgebraicCurveLibrary.Exapmles
{
    public class Circle : Ellipse
    {
        private const float DefaultRadius = 200f;

        float radius;

        public float Radius
        {
            get
            {
                return radius;
            }
        }

        /// <summary>
        /// Creates circle with radius
        /// </summary>
        /// <param name="radius">radius of the circle</param>
        public Circle(float radius) : base("Circle", radius, radius)
        {
            this.radius = radius;
        }

        /// <summary>
        /// Creates circle with default parameters
        /// </summary>
        /// <param name="radius">radius of the circle</param>
        public Circle() : base("Circle", DefaultRadius, DefaultRadius)
        {
            this.radius = DefaultRadius;
        }
    }
}
