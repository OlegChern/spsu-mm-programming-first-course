using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace DrawChartWpf.Charts
{
    /// <summary>
    /// график синуса
    /// </summary>
    class SinChart : Chart
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
