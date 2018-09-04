using System;

namespace Libs
{
    /// <summary>
    /// график косинуса
    /// </summary>
    public class CosChart : Chart
    {
        #region Methods
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        public CosChart(string name)
        {
            Name = name;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public override float CalcFunction(float value)
        {
            double v = value;
            return (float)Math.Cos(v);
        }
        #endregion
    }
}
