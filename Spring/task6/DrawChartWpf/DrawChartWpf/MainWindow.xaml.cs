using DrawChartWpf.Charts;
using System.Collections.Generic;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace DrawChartWpf
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Lists
        List<Point> points = new List<Point>();
        List<float> values = new List<float>();
        List<Chart> charts = new List<Chart>();
        #endregion

        #region Image
        #endregion

        #region Constructors
        public MainWindow()
        {
            InitializeComponent();


            for (double i = -100; i < 100; i += 0.1)
                values.Add((float)i);
            //charts.Add(new CosChart("Cos"));
            //charts.Add(new SinChart("Sin"));
            charts.Add(new SqEqChart("Парабола", false));
            charts.Add(new CircleChart("Окружность", true));
            cmbCharts.ItemsSource = charts;
            //грид управления
            gridControl.Visibility = Visibility.Collapsed;
        }
        #endregion

        #region Methods
        private Point MovePoint(Point p, double x, double y)
        {
            return new Point(p.X + x, p.Y + y);
        }

        private Point InverseY(Point p)
        {
            return new Point(p.X, -p.Y);
        }

        private Point InverseX(Point p)
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

        public List<Point> Scale(List<Point> points, double scale)
        {
            for (int i = 0; i < points.Count; i++)
                points[i] = new Point(points[i].X * scale, points[i].Y * scale);
            return points;
        }

        private void RepaintImage(List<Point> points)
        {
            if (points != null)
            {
                int dx = 50, dy = 50;

                DrawingVisual visual = new DrawingVisual();
                DrawingContext context = visual.RenderOpen();
                RenderTargetBitmap bm = new RenderTargetBitmap(500, 500, 500, 500, PixelFormats.Pbgra32);

                Brush brush = new SolidColorBrush(Colors.Black);
                Pen pen = new Pen(brush, 1);

                for (int i = 0; i < points.Count - 1; i++)
                {
                    Point p1 = MovePoint(InverseY(points[i]), dx, dy);
                    Point p = MovePoint(InverseY(points[i + 1]), dx, dy);
                    context.DrawLine(pen, p, p1);
                }
                context.Close();
                bm.Render(visual);
                imgChart.Source = bm;
            }
        }

        private List<Point> GetPoints(int index)
        {
            if (index > -1 && index < charts.Count)
                return charts[cmbCharts.SelectedIndex].GetPoints(values);
            return null;
        }

        #endregion

        #region Events
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            points = GetPoints(cmbCharts.SelectedIndex);
            RepaintImage(points);
        }

        private void btnLeft_Click(object sender, RoutedEventArgs e)
        {
            points = Move(-10, 0, points);
            RepaintImage(points);
        }

        private void btnRight_Click(object sender, RoutedEventArgs e)
        {
            points = Move(10, 0, points);
            RepaintImage(points);
        }

        private void btnUp_Click(object sender, RoutedEventArgs e)
        {
            points = Move(0, -10, points);
            RepaintImage(points);
        }

        private void btnDown_Click(object sender, RoutedEventArgs e)
        {
            points = Move(0, 10, points);
            RepaintImage(points);
        }

        private void btnInvert_Click(object sender, RoutedEventArgs e)
        {
            points = InvertY(points);
            RepaintImage(points);
        }

        private void btnInc_Click(object sender, RoutedEventArgs e)
        {
            points = Scale(points, 2);
            RepaintImage(points);
        }

        private void btnDec_Click(object sender, RoutedEventArgs e)
        {
            points = Scale(points, 0.5);
            RepaintImage(points);
        }

        private void Dec()
        {
            points = Scale(points, 0.9);
            RepaintImage(points);
        }

        private void Inc()
        {
            points = Scale(points, 1.1);
            RepaintImage(points);
        }
        private void mainWindows_MouseWheel(object sender, System.Windows.Input.MouseWheelEventArgs e)
        {
            int dx = e.Delta;
            //inc
            if (dx > 0)
            {
                Inc();
            }
            //dec
            else
            {
                Dec();
            }
        }

        private void imgChart_SourceUpdated(object sender, System.Windows.Data.DataTransferEventArgs e)
        {
            //imgChart.Source = bm;
        }
        #endregion
    }
}
