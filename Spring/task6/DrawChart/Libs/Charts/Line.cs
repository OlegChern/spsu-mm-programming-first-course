using System.Collections.Generic;
using System.Windows;

namespace Libs.Charts
{
    /// <summary>
    /// Линия
    /// </summary>
    public class Line
    {
        #region Fields
        /// <summary>
        /// точка 1
        /// </summary>
        Point p1;
        /// <summary>
        /// точка 2
        /// </summary>
        Point p2;
        #endregion
        #region Methods
        /// <summary>
        /// 
        /// </summary>
        public Line()
        {
            p1 = new Point(0, 0);
            p2 = new Point(0, 0);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="x1"></param>
        /// <param name="y1"></param>
        public Line(double x, double y, double x1, double y1)
        {
            Init(x, y, x1, y1);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="p1"></param>
        /// <param name="p2"></param>
        public Line(Point p1, Point p2)
        {
            Init(p1.X, p1.Y, p2.X, p2.Y);
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
        /// <param name="points"></param>
        public void SetPoints(List<Point> points)
        {
            if (points.Count > 1)
            {
                p1 = points[0];
                p2 = points[1];
            }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public List<Point> GetPoints()
        {
            return GetPoints(1);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="scale"></param>
        /// <returns></returns>
        public List<Point> GetPoints(double scale)
        {
            List<Point> points = new List<Point>();
            points.Add(p1);
            points.Add(p2);
            return Scale(points, scale);
        }
        /// <summary>
        /// Инициализирует прямую через 4 координаты
        /// </summary>
        /// <param name="x1">х первой точки</param>
        /// <param name="y1">y первой точки</param>
        /// <param name="x2">x второй точки</param>
        /// <param name="y2">y второй точки</param>
        private void Init(double x1, double y1, double x2, double y2)
        {
            p1 = new Point(x1, y1);
            p2 = new Point(x2, y2);
        }
        #endregion
    }
}
