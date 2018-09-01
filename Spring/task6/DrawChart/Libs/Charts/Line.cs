using System;
using System.Collections.Generic;
using System.Windows;

namespace Libs.Charts
{
    public class Line
    {
        /// <summary>
        /// точка 1
        /// </summary>
        Point p1;
        /// <summary>
        /// точка 2
        /// </summary>
        Point p2;
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
        public Line()
        {
            p1 = new Point(0, 0);
            p2 = new Point(0, 0);
        }
        public Line(double x, double y, double x1, double y1)
        {
            Init(x, y, x1, y1);
        }
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
        public void SetPoints(List<Point> points)
        {
            if (points.Count > 1)
            {
                p1 = points[0];
                p2 = points[1];
            }
        }
        public List<Point> GetPoints()
        {
            return GetPoints(1);
        }
        public List<Point> GetPoints(double scale)
        {
            List<Point> points = new List<Point>();
            points.Add(p1);
            points.Add(p2);
            return Scale(points, scale);
        }
        private void Init(double x, double y, double x1, double y1)
        {
            p1 = new Point(x, y);
            p2 = new Point(x1, y1);
        }
    }
}
