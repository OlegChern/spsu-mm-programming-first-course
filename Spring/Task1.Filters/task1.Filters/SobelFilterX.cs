namespace Task1.Filters
{
    public class SobelFilterX : AFilterMatrix
    {
        public SobelFilterX() : base(new double[3, 3] { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } })
        {
        }
    }
}
