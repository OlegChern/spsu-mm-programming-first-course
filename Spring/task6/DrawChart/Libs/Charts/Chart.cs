using System.Collections.Generic;
using System.Windows;

namespace Libs
{
    public abstract class Chart
    {
        #region Fields
        /// <summary>
        /// имя графика
        /// </summary>
        string name;
        /// <summary>
        /// отражать по Х
        /// </summary>
        bool mirror;
        /// <summary>
        /// имя графика
        /// </summary>
        public string Name { get => name; set => name = value; }
        /// <summary>
        /// отражать по Х
        /// </summary>
        public bool Mirror { get => mirror; set => mirror = value; }
        #endregion

        #region Methods
        public Chart()
        {
            Mirror = false;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        public Chart(string name)
        {
            Name = name;
            Mirror = false;
        }
        public Chart(string name, bool mirror)
        {
            Name = name;
            this.Mirror = mirror;
        }
        /// <summary>
        /// масштабирует график
        /// </summary>
        /// <param name="points"></param>
        /// <param name="scale"></param>
        /// <returns></returns>
        private List<Point> Scale(List<Point> points, double scale)
        {
            for (int i = 0; i < points.Count; i++)
                points[i] = new Point(points[i].X * scale, points[i].Y * scale);
            return points;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <returns></returns>
        public abstract float CalcFunction(float value);
        /// <summary>
        /// 
        /// </summary>
        /// <param name="values"></param>
        /// <returns></returns>
        public List<Point> GetPoints(List<float> values)
        {
            return GetPoints(values, 1);
        }
        /// <summary>
        /// получает точки Y для отрисовки графика
        /// </summary>
        /// <param name="values">значения X</param>
        /// <param name="mirror">отражать график по оси Y</param>
        /// <returns></returns>
        public List<Point> GetPoints(List<float> values, double scale)
        {
            List<Point> points = new List<Point>();
            if (Mirror)
            {

                for (int i = 0; i < values.Count; i++)
                    points.Add(new Point(values[i], CalcFunction(values[i])));
                for (int i = values.Count - 1; i > -1; i--)
                    points.Add(new Point(values[i], -CalcFunction(values[i])));
            }
            else
            {
                foreach (var item in values)
                    points.Add(new Point(item, CalcFunction(item)));
            }
            return Scale(points, scale);
        }
        #endregion

    }
}
