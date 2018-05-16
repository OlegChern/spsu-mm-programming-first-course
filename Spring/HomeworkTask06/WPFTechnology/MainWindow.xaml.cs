using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Drawing;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using AlgebraicCurveLibrary;
using AlgebraicCurveLibrary.Exapmles;

namespace WPFTechnology
{
    using WPoint = System.Windows.Point;

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        delegate void Do();

        Model model;

        public MainWindow()
        {
            InitializeComponent();

            // when all loaded, start initializing model
            Loaded += delegate
            {
                model = new Model();

                ScaleUpBtn.Click += new RoutedEventHandler(model.ScaleUp);
                ScaleDownBtn.Click += new RoutedEventHandler(model.ScaleDown);

                model.EnableScaleUpBtn += (bool x) => ScaleUpBtn.IsEnabled = x;
                model.EnableScaleDownBtn += (bool x) => ScaleDownBtn.IsEnabled = x;

                Curve parabola = new Parabola();

                PointF[][] points = parabola.GetDrawingPoints(new Vector2(0,0), new Vector2((float)DrawingCanvas.ActualWidth, (float)DrawingCanvas.ActualHeight));
                PathFigure[] figures = new PathFigure[points.Length];
                WPoint lastPoint = new WPoint();

                for (int i = 0; i < points.Length; i++)
                {
                    figures[i] = new PathFigure();

                    List<WPoint> partPoints = new List<WPoint>();

                    foreach(PointF point in points[i])
                    {
                        WPoint converted = new WPoint(point.X + DrawingCanvas.ActualWidth / 2, point.Y + DrawingCanvas.ActualHeight / 2);
                        partPoints.Add(converted);

                        lastPoint = converted;
                    }

                    figures[i].Segments.Add(new PolyBezierSegment(partPoints, true));
                }

                figures[points.Length - 1].StartPoint = lastPoint;

                DrawingPath.Data = new PathGeometry(figures);
            };
        }
    }
}
