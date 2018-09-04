using System.Collections.Generic;
using System.Windows;

namespace Libs.Charts
{
    /// <summary>
    /// Отрисовывет график
    /// </summary>
    public class ChartHelper
    {
        #region Fields
        /// <summary>
        /// 
        /// </summary>
        private double scaleInner = 1.0;
        /// <summary>
        /// 
        /// </summary>
        public double Scale
        {
            get
            {
                return scaleInner;
            }
            set
            {
                if (value > 1 && value < 5)
                    scaleInner = value;
            }
        }
        /// <summary>
        /// 
        /// </summary>
        public enum Direction
        {
            horizontal,
            vertical
        }
        #endregion
        #region Methods
        /// <summary>
        /// 
        /// </summary>
        /// <param name="p"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public Point MovePoint(Point p, double x, double y)
        {
            return new Point(p.X + x, p.Y + y);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="p"></param>
        /// <returns></returns>
        public Point InverseY(Point p)
        {
            return new Point(p.X, -p.Y);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="p"></param>
        /// <returns></returns>
        public Point InverseX(Point p)
        {
            return new Point(-p.X, p.Y);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="dx"></param>
        /// <param name="dy"></param>
        /// <param name="points"></param>
        /// <returns></returns>
        public List<Point> Move(double dx, double dy, List<Point> points)
        {
            for (int i = 0; i < points.Count; i++)
                points[i] = new Point(points[i].X + dx, points[i].Y + dy);
            return points;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="points"></param>
        /// <returns></returns>
        public List<Point> InvertY(List<Point> points)
        {
            for (int i = 0; i < points.Count; i++)
                points[i] = InverseY(points[i]);
            return points;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="charts"></param>
        /// <param name="values"></param>
        /// <param name="scale"></param>
        /// <param name="index"></param>
        /// <returns></returns>
        public List<Point> GetPoints(List<Chart> charts, List<float> values, double scale, int index)
        {
            if (index > -1 && index < charts.Count)
                return charts[index].GetPoints(values, scale);
            return null;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="lines"></param>
        /// <param name="scale"></param>
        /// <returns></returns>
        private List<Line> UpdateScale(List<Line> lines, double scale)
        {
            foreach (Line line in lines)
                line.SetPoints(line.GetPoints(scale));
            return lines;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="p"></param>
        /// <param name="size"></param>
        /// <param name="scale"></param>
        /// <param name="direction"></param>
        /// <returns></returns>
        public List<Line> DrawAxis(Point p, Size size, double scale, Direction direction)
        {
            return DrawAxis(p.X, p.Y, size.Width, size.Height, scale, direction);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="scale"></param>
        /// <param name="direction"></param>
        /// <returns></returns>
        public List<Line> DrawAxis(double x, double y, double width, double height, double scale, Direction direction)
        {
            List<Line> lines = new List<Line>();
            if (direction == Direction.horizontal)
                lines.AddRange(DrawHorAxis(y, 3, width, height, scale));
            else
                lines.AddRange(DrawVertAxis(x, 3, width, height, scale));
            return UpdateScale(lines, scale);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="coord"></param>
        /// <param name="size"></param>
        /// <param name="step"></param>
        /// <param name="markSize"></param>
        /// <param name="direction"></param>
        /// <returns></returns>
        private List<Line> DrawMarks(double coord, double size, double step, double markSize, Direction direction)
        {
            List<Line> lines = new List<Line>();
            if (direction == Direction.horizontal)
            {
                double x = -size / 2;
                while (x < size / 2)
                {
                    //int dy = 5;
                    lines.Add(
                        new Line(
                        new Point(x, coord + markSize / 2),
                        new Point(x, coord - markSize / 2)
                        ));
                    x += step;
                }
            }
            if (direction == Direction.vertical)
            {
                double y = -size / 2;
                while (y < size / 2)
                {
                    //int dx = 5;
                    lines.Add(
                        new Line(
                        new Point(coord + markSize / 2, y),
                        new Point(coord - markSize / 2, y)
                        ));
                    y += 10;
                }
            }
            return lines;
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="y"></param>
        /// <param name="dy"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="scale"></param>
        /// <returns></returns>
        private List<Line> DrawHorAxis(double y, double dy, double width, double height, double scale)
        {
            List<Line> lines = new List<Line>();
            lines.Add(
                new Line(
                new Point(-width / 2, y),
                new Point(width / 2, y)
                ));
            //lines = DrawMarks(y, 5, 10, 10, Direction.horizontal);
            return UpdateScale(lines, scale);
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="dx"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        /// <param name="scale"></param>
        /// <returns></returns>
        private List<Line> DrawVertAxis(double x, double dx, double width, double height, double scale)
        {
            List<Line> lines = new List<Line>();
            lines.Add(
               new Line(
               new Point(x, -height / 2),
               new Point(x, height / 2)
               ));
            //lines = DrawMarks(x, 5, 10, 10, Direction.vertical);
            return UpdateScale(lines, scale);
        }
        #endregion
    }
}
