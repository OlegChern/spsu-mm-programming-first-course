using System;

namespace Libs
{
    /// <summary>
    /// график окружности
    /// </summary>
    public class CircleChart : Chart
    {
        #region Methods
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        public CircleChart(string name)
        {
            Name = name;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <param name="mirror"></param>
        public CircleChart(string name, bool mirror)
        {
            Name = name;
            base.mirror = mirror;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public override float CalcFunction(float value)
        {
            return (float)Math.Sqrt(-1 * (float)value * (float)value + 625);
        }
        #endregion
    }
}
