using System;

namespace Libs
{
    /// <summary>
    /// график косинуса
    /// </summary>
    public class CosChart : Chart
    {
        public CosChart(string _name)
        {
            title = _name;
        }
        public override float f(float value)
        {
            double v = value;
            return (float)Math.Cos(v);
        }
    }
}
