using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Libs;
using Libs.Charts;
namespace DrawChartWpf
{

    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Globals
        /// <summary>
        /// для работы с графиками и точками
        /// </summary>
        ChartHelper cHelper = new ChartHelper();
        /// <summary>
        /// текущий масштаб
        /// </summary>
        double _scaleCurr = 1;
        /// <summary>
        /// шаг масштабирования
        /// </summary>
        double scaleStep = 0.1;
        /// <summary>
        /// текущий масштаб
        /// </summary>
        public double scaleCurr
        {
            set
            {
                _scaleCurr = Math.Max(1, value);
            }
            get
            {
                return _scaleCurr;
            }
        }

        public object Graphics { get; private set; }
        #endregion

        #region Lists
        List<System.Windows.Point> points = new List<System.Windows.Point>();
        List<float> values = new List<float>();
        List<Chart> charts = new List<Chart>();
        List<Line> lines = new List<Line>();
        #endregion

        #region Image
        #endregion

        #region Constructors
        public MainWindow()
        {
            InitializeComponent();
            for (double i = -100; i < 100; i += 0.1)
                values.Add((float)i);
            charts.Add(new SqEqChart("Парабола", false));
            charts.Add(new CircleChart("Окружность", true));
            cmbCharts.ItemsSource = charts;
        }
        #endregion

        #region Methods

        private void DrawPoints(List<Point> points, int dx, int dy, ref DrawingContext context)
        {
            Brush brush = new SolidColorBrush(Colors.Black);
            Pen pen = new Pen(brush, 0.2);
            for (int i = 0; i < points.Count - 1; i++)
            {
                Point p1 = cHelper.MovePoint(cHelper.InverseY(points[i]), dx, dy);
                Point p = cHelper.MovePoint(cHelper.InverseY(points[i + 1]), dx, dy);
                context.DrawLine(pen, p, p1);
            }
        }
        private void DrawPoints(List<Line> lines, int dx, int dy, ref DrawingContext context)
        {
            foreach (Line line in lines)
                DrawPoints(line.GetPoints(), dx, dy, ref context);
        }
        private void UpdateImage()
        {
            UpdatePoints();
            if (points != null)
            {
                int dx = 50, dy = 50;

                DrawingVisual visual = new DrawingVisual();
                DrawingContext context = visual.RenderOpen();
                RenderTargetBitmap image = new RenderTargetBitmap(500, 500, 500, 500, PixelFormats.Pbgra32);

                DrawPoints(points, dx, dy, ref context);
                DrawPoints(lines, dx, dy, ref context);

                context.Close();
                image.Render(visual);
                imgChart.Source = image;
            }
        }
        private void UpdatePoints()
        {
            points.Clear();
            lines.Clear();
            Point p = new System.Windows.Point(0, 0);
            Size size = new System.Windows.Size(Width, Height);
            lines.AddRange(cHelper.DrawAxis(p, size, scaleCurr, ChartHelper.Direction.horizontal));
            lines.AddRange(cHelper.DrawAxis(p, size, scaleCurr, ChartHelper.Direction.vertical));
            points = cHelper.GetPoints(charts, values, scaleCurr, cmbCharts.SelectedIndex);
        }
        private void Dec()
        {
            scaleCurr -= scaleStep;
            UpdateImage();
        }
        private void Inc()
        {
            scaleCurr += scaleStep;
            UpdateImage();
        }
        #endregion

        #region Events
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            UpdateImage();
        }
        private void btnLeft_Click(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(-10, 0, points);
            //UpdateImage(points);
        }
        private void btnRight_Click(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(10, 0, points);
            //UpdateImage(points);
        }
        private void btnUp_Click(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(0, -10, points);
            //UpdateImage(points);
        }
        private void btnDown_Click(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(0, 10, points);
            //UpdateImage(points);
        }
        private void btnInvert_Click(object sender, RoutedEventArgs e)
        {
            //points = cHelper.InvertY(points);
            //UpdateImage(points);
        }
        private void btnInc_Click(object sender, RoutedEventArgs e)
        {
            Inc();
        }
        private void btnDec_Click(object sender, RoutedEventArgs e)
        {
            Dec();
        }
        private void mainWindows_MouseWheel(object sender, System.Windows.Input.MouseWheelEventArgs e)
        {
            if (e.Delta > 0)
                Inc();
            else
                Dec();
        }
        #endregion
    }
}
