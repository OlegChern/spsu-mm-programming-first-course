using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace DrawChartWpf.Charts
{
    /// <summary>
    /// график квадратного уравнения
    /// </summary>
    class SqEqChart : Chart
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
