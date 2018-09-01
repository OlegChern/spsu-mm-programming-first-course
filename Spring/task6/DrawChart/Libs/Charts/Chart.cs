using System;
using System.Collections.Generic;
using System.Windows;

namespace Libs
{
    public abstract class Chart
    {
        /// <summary>
        /// имя графика
        /// </summary>
        public string title { set; get; }
        ///// <summary>
        ///// масштаб
        ///// </summary>
        //private double _scale = 1;
        ///// <summary>
        ///// масштаб
        ///// </summary>
        //public double scale
        //{
        //    set
        //    {
        //        scale = Math.Max(0.1, value);
        //    }
        //    get
        //    {
        //        return _scale;
        //    }
        //}
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
        public abstract float f(float value);

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
            if (mirror)
            {

                for (int i = 0; i < values.Count; i++)
                    points.Add(new Point(values[i], f(values[i])));
                for (int i = values.Count - 1; i > -1; i--)
                    points.Add(new Point(values[i], -f(values[i])));
            }
            else
            {
                foreach (var item in values)
                    points.Add(new Point(item, f(item)));
            }
            return Scale(points, scale);
        }
    }
}
