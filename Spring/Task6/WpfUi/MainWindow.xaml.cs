using System.Collections.Generic;
using System.Net;
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
        public MainWindow()
        {
            InitializeComponent();
            FunctionSelectionBox.ItemsSource = new List<CurveInfo>
            {
                new CircleInfo(3, new Point(1, 2)),
                new EllipticCurveInfo()
            };

            FunctionSelectionBox.SelectionChanged += (a, b) => Paint(b.AddedItems[0] as CurveInfo);
            
        }

        void Paint(CurveInfo curve)
        {
            // new Canvas().
            PaintDot(Canvas, new Point(120, 120));
        }

        static void PaintDot(Panel canvas, Point coordinates)
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
            canvas.Children.Add(currentDot);
        }
    }
}
