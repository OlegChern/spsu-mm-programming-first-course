using System;

namespace Libs
{
    public class CircleChart : Chart
    {
        public CircleChart(string _name)
        {
            title = _name;
        }
        public CircleChart(string _name, bool _mirror)
        {
            title = _name;
            mirror = _mirror;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public override float f(float value)
        {
            return (float)Math.Sqrt(-1 * (float)value * (float)value + 625);
        }
    }
}
