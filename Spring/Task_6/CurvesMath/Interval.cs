namespace CurvesMath
{
    public struct Interval
    {
        public double Begin { get; set; }
        public double End { get; set; }


        public Interval(double beg, double end)
        {
            Begin = beg;
            End = end;
        }
    }
}
