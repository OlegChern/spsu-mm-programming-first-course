namespace Task1.Filters
{
    public class GaussFilter : AFilterMatrix
    {
        public GaussFilter() : base(new double[3, 3] { { 0.0625, 0.125, 0.0625 }, { 0.125, 0.25, 0.125 }, { 0.0625, 0.125, 0.0625 } })
        {
        }
    }
}
