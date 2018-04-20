using Math;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;

namespace WpfUi
{
    sealed class WpfPainter : Painter
    {
        Panel panel;

        SolidColorBrush brush;

        public WpfPainter(Panel panel)
        {
            this.panel = panel;
            brush = new SolidColorBrush(Colors.Green);
        }

        protected override double ScreenWidth => panel.ActualWidth;

        protected override double ScreenHeight => panel.ActualHeight;

        protected override void Clear()
        {
            panel.Children.Clear();
        }

        protected override void PaintAxes()
        {
            panel.Children.Add(new Line
            {
                Stroke = Brushes.LightSteelBlue,
                X1 = ScreenWidth / 2,
                X2 = ScreenWidth / 2,
                Y1 = 0,
                Y2 = ScreenHeight,
                StrokeThickness = 2
            });

            panel.Children.Add(new Line
            {
                Stroke = Brushes.LightSteelBlue,
                X1 = 0,
                X2 = ScreenWidth,
                Y1 = ScreenHeight / 2,
                Y2 = ScreenHeight / 2,
                StrokeThickness = 2
            });
        }

        protected override void PaintDot(Math.Point dot)
        {
            var currentDot = new Ellipse
            {
                Stroke = brush,
                StrokeThickness = 3
            };
            Panel.SetZIndex(currentDot, 3);
            currentDot.Height = PointSize;
            currentDot.Width = PointSize;
            currentDot.Fill = new SolidColorBrush(Colors.Green);
            currentDot.Margin = new Thickness(dot.Y, dot.X, 0, 0);
            panel.Children.Add(currentDot);
        }
    }
}
