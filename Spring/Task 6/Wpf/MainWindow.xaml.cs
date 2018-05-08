using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using MathInfo;
using System.Drawing;

namespace Wpf
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public PointCollection PositivePoints { get; private set; }

        public PointCollection NegativePoints { get; private set; }

        public CurveInfo Curve { get; private set; }

        public System.Windows.Size StartSize { get; private set; }

        private double scalePaint;
        public double ScalePaint
        {
            get
            {
                return scalePaint;
            }
            set
            {
                if (value > 1)
                {
                    scalePaint = 1;
                }
                else if (value < 0.1)
                {
                    scalePaint = 0.1;
                }
                else
                {
                    scalePaint = value;
                }
            }
        }

        public MainWindow()
        {
            InitializeComponent();
            Curve = new CurveInfo();
            ScalePaint = 0.5;
            Loaded += (sender, args) => StartSize = new System.Windows.Size(graphic.ActualWidth, graphic.ActualHeight);
            MouseWheel += (sender, args) => 
            {
                ScalePaint += (args.Delta > 0) ? 0.05 : -0.05;
                if ((PositivePoints != null) && (NegativePoints != null))
                {
                    Paint();
                }
            };
            SizeChanged += (sender, args) =>
            {
                if ((PositivePoints != null) && (NegativePoints != null))
                {
                    Paint();
                }
            };
        }

        public void ChangeGraphic(object sender, EventArgs args)
        {
            Curve.BoxCurve = (Curve)(((ComboBox)sender).SelectedItem);
            Paint();
        }

        public void BuildingPoints()
        {
            var region = new MathInfo.Region(new System.Drawing.Point(0, 0), new System.Drawing.Point((int)gridColumn.ActualWidth, (int)gridRow.ActualHeight));
            PositivePoints = new PointCollection();
            NegativePoints = new PointCollection();
            Curve.BoxCurve.BuildCurve(region, ScalePaint);
            Curve.BoxCurve.PositivePoints.ForEach(p => PositivePoints.Add(new System.Windows.Point(p.X, p.Y)));
            Curve.BoxCurve.NegativePoints.ForEach(p => NegativePoints.Add(new System.Windows.Point(p.X, p.Y)));
            graphic.RenderTransform = new TranslateTransform(region.Width / 2, region.Height / 2);
            graphicSystem.RenderTransform = new TranslateTransform(region.Width / 2, region.Height / 2);
        }

        public void Paint()
        {
            BuildingPoints();
            PaintSystem();
            PaintGraphic();
        }

        public void PaintGraphic()
        {
            graphic.StrokeThickness = 2;
            var geometry = new PathGeometry();
            if ((PositivePoints.Count != 0) && (NegativePoints.Count != 0))
            {
                PolyLineSegment segmentPositive = new PolyLineSegment() { Points = PositivePoints };
                LineSegment segmentInvisible = new LineSegment() { Point = NegativePoints.First(), IsStroked = (Curve.BoxCurve is Ellips) ? true : false };
                PolyLineSegment segmentNegative = new PolyLineSegment() { Points = NegativePoints };
                PathFigure graph = new PathFigure() { IsClosed = (Curve.BoxCurve is Ellips) ? true : false, StartPoint = segmentPositive.Points.First() };
                graph.Segments.Add(segmentPositive);
                graph.Segments.Add(segmentInvisible);
                graph.Segments.Add(segmentNegative);
                geometry.Figures.Add(graph);
            }
            graphic.Data = geometry;
        }

        public void PaintSystem()
        {
            graphicSystem.StrokeThickness = 0.5;
            var geometry = new PathGeometry();
            PathFigure lineHorizont = new PathFigure() { StartPoint = new System.Windows.Point(graphic.ActualWidth / 2, 0) };
            lineHorizont.Segments.Add(new LineSegment(new System.Windows.Point(- graphic.ActualWidth / 2, 0), true));
            geometry.Figures.Add(lineHorizont);
            PathFigure lineVertical = new PathFigure() { StartPoint = new System.Windows.Point(0, graphic.ActualHeight / 2) };
            lineVertical.Segments.Add(new LineSegment(new System.Windows.Point(0, - graphic.ActualHeight / 2), true));
            geometry.Figures.Add(lineVertical); 
            int step = (int)(StartSize.Width / 10 * ScalePaint);
            for (int i = 0; i < (int)graphic.ActualWidth / 2; i += step)
            {
                var line = new PathFigure() { StartPoint = new System.Windows.Point(i, -5)};
                line.Segments.Add(new LineSegment(new System.Windows.Point(i, 5), true));
                line.Segments.Add(new LineSegment(new System.Windows.Point(-i, -5), false));
                line.Segments.Add(new LineSegment(new System.Windows.Point(-i, 5), true));
                geometry.Figures.Add(line);
            }
            for (int i = 0; i < (int)graphic.ActualHeight / 2; i += step)
            {
                var line = new PathFigure() { StartPoint = new System.Windows.Point(-5, i) };
                line.Segments.Add(new LineSegment(new System.Windows.Point(5, i), true));
                line.Segments.Add(new LineSegment(new System.Windows.Point(-5, -i), false));
                line.Segments.Add(new LineSegment(new System.Windows.Point(5, -i), true));
                geometry.Figures.Add(line);
            }
            graphicSystem.Data = geometry;
        }
    }
}
