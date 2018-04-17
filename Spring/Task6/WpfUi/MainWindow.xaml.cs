using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;
using Math;
using Point = Math.Point;

namespace WpfUi
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        int pixelsInUnit;

        public MainWindow()
        {
            pixelsInUnit = 64;

            InitializeComponent();
            FunctionSelectionBox.ItemsSource = new List<CurveInfo>
            {
                // new CentralCircleInfo(2),
                new CircleInfo(2, 1, 2),
                new EllipticCurveInfo()
            };

            FunctionSelectionBox.SelectionChanged += (a, b) => Paint(b.AddedItems[0] as CurveInfo);

            PlusButton.Click += (sender, args) =>
            {
                if (pixelsInUnit < 512)
                {
                    pixelsInUnit *= 2;
                    PlusButton.IsEnabled = true;
                    MinusButton.IsEnabled = true;
                }
                else
                {
                    pixelsInUnit = 1024;
                    PlusButton.IsEnabled = false;
                    MinusButton.IsEnabled = true;
                }

                Paint(FunctionSelectionBox.SelectionBoxItem as CurveInfo);
            };

            MinusButton.Click += (sender, args) =>
            {
                if (pixelsInUnit > 2)
                {
                    pixelsInUnit /= 2;
                    PlusButton.IsEnabled = true;
                    MinusButton.IsEnabled = true;
                }
                else
                {
                    pixelsInUnit = 1;
                    PlusButton.IsEnabled = true;
                    MinusButton.IsEnabled = false;
                }
                
                Paint(FunctionSelectionBox.SelectionBoxItem as CurveInfo);
            };

            SizeChanged += (sender, args) => Paint(FunctionSelectionBox.SelectionBoxItem as CurveInfo);
        }

        void Paint(CurveInfo curve)
        {
            Canvas.Children.Clear();
            
            PaintAxes(Canvas);

            if (curve is null)
            {
                return;
            }
            
            var zeroPoint = new Point(Canvas.ActualHeight / 2, Canvas.ActualWidth / 2);

            var upperLeft = new Point(-Canvas.ActualWidth / 2, -Canvas.ActualHeight / 2) / pixelsInUnit;

            var lowerRight = new Point(Canvas.ActualWidth / 2, Canvas.ActualHeight / 2) / pixelsInUnit;

            var realPoints =
                from point in curve.GetPoints(new Region(upperLeft, lowerRight))
                let realPoint = new Point(point.Y, point.X) * pixelsInUnit + zeroPoint
                where realPoint.X >= 0
                      && realPoint.X <= Canvas.ActualHeight
                      && realPoint.Y >= 0
                      && realPoint.Y <= Canvas.ActualWidth
                select realPoint;

            realPoints.ForEach(point => PaintDot(Canvas, point));
        }

        static void PaintDot(Panel panel, Point coordinates)
        {
            const int dotSize = 3;

            var currentDot = new Ellipse
            {
                Stroke = new SolidColorBrush(Colors.Green),
                StrokeThickness = 3
            };
            Panel.SetZIndex(currentDot, 3);
            currentDot.Height = dotSize;
            currentDot.Width = dotSize;
            currentDot.Fill = new SolidColorBrush(Colors.Green);
            currentDot.Margin = new Thickness(coordinates.Y, coordinates.X, 0, 0); // Sets the position.
            panel.Children.Add(currentDot);
        }

        static void PaintAxes(Panel panel)
        {
            panel.Children.Add(new Line
            {
                Stroke = Brushes.LightSteelBlue,
                X1 = panel.ActualWidth / 2,
                X2 = panel.ActualWidth / 2,
                Y1 = 0,
                Y2 = panel.ActualHeight,
                StrokeThickness = 2
            });

            panel.Children.Add(new Line
            {
                Stroke = Brushes.LightSteelBlue,
                X1 = 0,
                X2 = panel.ActualWidth,
                Y1 = panel.ActualHeight / 2,
                Y2 = panel.ActualHeight / 2,
                StrokeThickness = 2
            });
        }
    }
}
