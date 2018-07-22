using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace DrawChartWpf.Charts
{
    /// <summary>
    /// график косинуса
    /// </summary>
    class CosChart : Chart
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
