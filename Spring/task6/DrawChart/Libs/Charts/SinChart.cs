using System;

namespace Libs
{
    /// <summary>
    /// график синуса
    /// </summary>
    public class SinChart : Chart
    {
        public SinChart(string _name)
        {
            title = _name;
        }
        public override float f(float value)
        {
            double v = value;
            return (float)Math.Sin(v);
        }
    }
}
