namespace Task1.Filters
{
    public class SobelFilterY : AFilterMatrix
    {
        public SobelFilterY() : base(new double[3, 3] { { -1, -2, -1 }, { 0, 0, 0 }, { 1, 2, 1 } })
        {
        }
    }
}
