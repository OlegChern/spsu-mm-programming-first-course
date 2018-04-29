namespace Task1.Filters
{
    public class AverageFilter : AFilterMatrix
    {
        public AverageFilter() : base(new double[3, 3] { { 0.1111, 0.1111, 0.1111 }, { 0.1111, 0.1111, 0.1111 }, { 0.1111, 0.1111, 0.1111 } })
        {
        }
    }
}
