using System.Collections.Generic;
using System.Windows;

namespace DrawChartWpf.Charts
{
    abstract class Chart
    {
        /// <summary>
        /// имя графика
        /// </summary>
        public string title { set; get; }
        /// <summary>
        /// отражать по Х
        /// </summary>
        public bool mirror;
        public Chart()
        {
            mirror = false;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="_name"></param>
        public Chart(string _name)
        {
            title = _name;
            mirror = false;
        }
        public Chart(string _name, bool _mirror)
        {
            title = _name;
            mirror = _mirror;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public abstract float f(float value);
        /// <summary>
        /// получает точки Y для отрисовки графика
        /// </summary>
        /// <param name="values">значения X</param>
        /// <param name="mirror">отражать график по оси Y</param>
        /// <returns></returns>
        public List<Point> GetPoints(List<float> values)
        {
            if (mirror)
            {
                List<Point> points = new List<Point>();
                for (int i = 0; i < values.Count; i++)
                    points.Add(new Point(values[i], f(values[i])));
                for (int i = values.Count - 1; i > -1; i--)
                    points.Add(new Point(values[i], -f(values[i])));
                return points;
            }
            else
            {
                List<Point> points = new List<Point>();
                foreach (var item in values)
                    points.Add(new Point(item, f(item)));
                return points;
            }
        }
    }
}
