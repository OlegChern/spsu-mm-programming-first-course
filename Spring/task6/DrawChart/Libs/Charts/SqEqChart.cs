namespace Libs
{
    /// <summary>
    /// график квадратного уравнения
    /// </summary>
    public class SqEqChart : Chart
    {
        #region Methods
        public SqEqChart(string name)
        {
            Name = name;
        }
        public SqEqChart(string name, bool mirror)
        {
            Name = name;
            base.mirror = mirror;
        }
        public override float CalcFunction(float value)
        {
            return value * value;
        }
        #endregion
    }
}
