namespace Math
{
    public struct Point
    {
#if DEBUG
        public readonly double X;
        public readonly double Y;
#else
        public double X;
        public double Y;
#endif
        
        public Point(double x, double y)
        {
            this.X = x;
            this.Y = y;
        }

        public override string ToString()
        {
            return $"({X}, {Y})";
        }
    }
}
