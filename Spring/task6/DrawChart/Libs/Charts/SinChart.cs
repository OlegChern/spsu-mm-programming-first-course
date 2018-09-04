using System;

namespace Libs
{
    /// <summary>
    /// график синуса
    /// </summary>
    public class SinChart : Chart
    {
        #region Methods
        public SinChart(string name)
        {
            Name = name;
        }
        public override float CalcFunction(float value)
        {
            double v = value;
            return (float)Math.Sin(v);
        }
        #endregion
    }
}
