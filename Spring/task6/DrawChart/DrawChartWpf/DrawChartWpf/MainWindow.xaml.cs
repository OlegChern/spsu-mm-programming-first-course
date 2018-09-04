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

        #region Lists
        List<System.Windows.Point> points = new List<System.Windows.Point>();
        List<float> values = new List<float>();
        List<Chart> charts = new List<Chart>();
        List<Line> lines = new List<Line>();
        #endregion

        #region Fields
        /// <summary>
        /// для работы с графиками и точками
        /// </summary>
        ChartHelper cHelper = new ChartHelper();
        /// <summary>
        /// текущий масштаб
        /// </summary>
        double scaleCurrInner = 1;
        /// <summary>
        /// шаг масштабирования
        /// </summary>
        double scaleStep = 0.1;
        #endregion

        #region Properties
        /// <summary>
        /// текущий масштаб
        /// </summary>
        double ScaleCurr
        {
            set
            {
                scaleCurrInner = Math.Max(1, value);
            }
            get
            {
                return scaleCurrInner;
            }
        }
        #endregion

        #endregion

        #region Constructors
        public MainWindow()
        {
            InitializeComponent();
            for (double i = -100; i < 100; i += 0.1)
                values.Add((float)i);
            charts.Add(new SqEqChart("Парабола", false));
            charts.Add(new CircleChart("Окружность", true));
            cbCharts.ItemsSource = charts;
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
            lines.AddRange(cHelper.DrawAxis(p, size, ScaleCurr, ChartHelper.Direction.horizontal));
            lines.AddRange(cHelper.DrawAxis(p, size, ScaleCurr, ChartHelper.Direction.vertical));
            points = cHelper.GetPoints(charts, values, ScaleCurr, cbCharts.SelectedIndex);
        }
        private void Dec()
        {
            ScaleCurr -= scaleStep;
            UpdateImage();
        }
        private void Inc()
        {
            ScaleCurr += scaleStep;
            UpdateImage();
        }
        #endregion

        #region Events
        private void CbChartsSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            UpdateImage();
        }
        private void BtnLeftClick(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(-10, 0, points);
            //UpdateImage(points);
        }
        private void BtnRightClick(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(10, 0, points);
            //UpdateImage(points);
        }
        private void BtnUpClick(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(0, -10, points);
            //UpdateImage(points);
        }
        private void BtnDownClick(object sender, RoutedEventArgs e)
        {
            //points = cHelper.Move(0, 10, points);
            //UpdateImage(points);
        }
        private void BtnInvertClick(object sender, RoutedEventArgs e)
        {
            //points = cHelper.InvertY(points);
            //UpdateImage(points);
        }
        private void BtnIncClick(object sender, RoutedEventArgs e)
        {
            Inc();
        }
        private void BtnDecClick(object sender, RoutedEventArgs e)
        {
            Dec();
        }
        private void MainWindowsMouseWheel(object sender, System.Windows.Input.MouseWheelEventArgs e)
        {
            if (e.Delta > 0)
                Inc();
            else
                Dec();
        }
        #endregion
    }
}
