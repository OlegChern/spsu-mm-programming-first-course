using System.Collections.Generic;
using System.Windows;

namespace Libs.Charts
{
    public class ChartHelper
    {
        private double _scale = 1.0;

        public double scale
        {
            get
            {
                return _scale;
            }
            set
            {
                if (value > 1 && value < 5)
                    _scale = value;
            }
        }

        public enum Direction
        {
            horizontal,
            vertical
        }
        public Point MovePoint(Point p, double x, double y)
        {
            return new Point(p.X + x, p.Y + y);
        }
        public Point InverseY(Point p)
        {
            return new Point(p.X, -p.Y);
        }
        public Point InverseX(Point p)
        {
            return new Point(-p.X, p.Y);
        }
        public List<Point> Move(double dx, double dy, List<Point> points)
        {
            for (int i = 0; i < points.Count; i++)
                points[i] = new Point(points[i].X + dx, points[i].Y + dy);
            return points;
        }
        public List<Point> InvertY(List<Point> points)
        {
            for (int i = 0; i < points.Count; i++)
                points[i] = InverseY(points[i]);
            return points;
        }
        public List<Point> GetPoints(List<Chart> charts, List<float> values, double scale, int index)
        {
            if (index > -1 && index < charts.Count)
                return charts[index].GetPoints(values, scale);
            return null;
        }
        private List<Line> Scale(List<Line> lines, double scale)
        {
            foreach (Line line in lines)
                line.SetPoints(line.GetPoints(scale));
            return lines;
        }
        public List<Line> DrawAxis(Point p, Size size, double scale, Direction direction)
        {
            return DrawAxis(p.X, p.Y, size.Width, size.Height, scale, direction);
        }
        public List<Line> DrawAxis(double x, double y, double width, double height, double scale, Direction direction)
        {
            List<Line> lines = new List<Line>();
            if (direction == Direction.horizontal)
                lines.AddRange(DrawHorAxis(y, 3, width, height, scale));
            else
                lines.AddRange(DrawVertAxis(x, 3, width, height, scale));
            return Scale(lines, scale);
        }
        //TODO:fix marks bug
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
        private List<Line> DrawHorAxis(double y, double dy, double width, double height, double scale)
        {
            List<Line> lines = new List<Line>();
            lines.Add(
                new Line(
                new Point(-width / 2, y),
                new Point(width / 2, y)
                ));
            //lines = DrawMarks(y, 5, 10, 10, Direction.horizontal);
            return Scale(lines, scale);
        }
        private List<Line> DrawVertAxis(double x, double dx, double width, double height, double scale)
        {
            List<Line> lines = new List<Line>();
            lines.Add(
               new Line(
               new Point(x, -height / 2),
               new Point(x, height / 2)
               ));
            //lines = DrawMarks(x, 5, 10, 10, Direction.vertical);
            return Scale(lines, scale);
        }
    }
}
