namespace Libs
{
    /// <summary>
    /// график квадратного уравнения
    /// </summary>
    public class SqEqChart : Chart
    {
        public SqEqChart(string _name)
        {
            title = _name;
        }
        public SqEqChart(string _name, bool _mirror)
        {
            title = _name;
            mirror = _mirror;
        }
        public override float f(float value)
        {
            return value * value;
        }
    }
}
