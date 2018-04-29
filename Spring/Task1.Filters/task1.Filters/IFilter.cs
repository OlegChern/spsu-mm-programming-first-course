namespace Task1.Filters
{
    public interface IFilter
    {
        RGB[,] Apply(RGB[,] startRGB);
    }
}
