using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Drawing;
using Curves;

namespace DrawCurves.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private float height;

        private float width;

        private float x0;

        private float y0;

        private float scale;

        private int pointsInSegment;

        public MainWindow()
        {
            InitializeComponent();

            height = (float)canvas.Height / 2;
            width = (float)canvas.Width / 2;

            x0 = (float)canvas.Width / 2;
            y0 = (float)canvas.Height / 2;

            small_Decrease.Tag = -0.1f;
            large_Decrease.Tag = -1f;
            small_Increase.Tag = 0.1f;
            large_Increase.Tag = 1f;
            scaleChangeLabel.Tag = 1f;

            List<ACurve> list = new List<ACurve>() { new Curves.Ellipse(1, 1, -width, width),
                new Curves.Ellipse(3, 0.5f, -width, width), new Hyperbola(1, 1, -width, width),
                new Hyperbola(5, 2, -width, width), new Parabola(0.5f, -width, width),
                new Parabola(-5, -width, width)};
            curvesComboBox.ItemsSource = list;
        }

        private void buttonScale_Click(object sender, RoutedEventArgs e)
        {
            float newTag = (float)scaleChangeLabel.Tag + (float)((sender as Button).Tag);
            scaleChangeLabel.Tag = (float)Math.Round(newTag, 1);
            if (((float)scaleChangeLabel.Tag > 0f) && ((float)scaleChangeLabel.Tag < 5f))
            {
                scaleChangeLabel.Content = scaleChangeLabel.Tag.ToString();
            }
            else
            {
                scaleChangeLabel.Tag = (float)scaleChangeLabel.Tag - (float)((sender as Button).Tag);
            }
        }

        private void DrawBlackLine(float x1, float y1, float x2, float y2)
        {
            Line line = new Line();
            line.X1 = x1;
            line.Y1 = y1;
            line.X2 = x2;
            line.Y2 = y2;
            line.Stroke = System.Windows.Media.Brushes.Black;
            line.StrokeThickness = 1;
            canvas.Children.Add(line);
        }

        private void DrawPoint(float x, float y, float size)
        {
            System.Windows.Shapes.Ellipse point = new System.Windows.Shapes.Ellipse();
            point.Width = size;
            point.Height = size;
            point.Fill = System.Windows.Media.Brushes.Black;
            Canvas.SetLeft(point, x - size / 2);
            Canvas.SetTop(point, y - size / 2);
            canvas.Children.Add(point);
        }

        private void DrawNumberX(float number, int pixelsInSegment)
        {
            number = (float)Math.Round(number, 1);
            TextBlock textBlock = new TextBlock();
            textBlock.Text = number.ToString();
            textBlock.FontSize = 10;
            Canvas.SetLeft(textBlock, x0 + number * pixelsInSegment - 5);
            Canvas.SetTop(textBlock, y0 + 6);
            canvas.Children.Add(textBlock);
        }

        private void DrawNumberY(float number, int pixelsInSegment)
        {
            number = (float)Math.Round(number, 1);
            TextBlock textBlock = new TextBlock();
            textBlock.Text = (-number).ToString();
            textBlock.FontSize = 10;
            Canvas.SetLeft(textBlock, x0 + 8);
            Canvas.SetTop(textBlock, y0 + number * pixelsInSegment - 8);
            canvas.Children.Add(textBlock);
        }

        private void DrawSystem(float step)
        {
            DrawBlackLine(x0 - width, y0, x0 + width, y0);
            DrawBlackLine(x0, y0 - height, x0, y0 + height);

            DrawPoint(x0, y0, 4);

            DrawBlackLine(x0 + width, y0, x0 + width - 5, y0 - 5);
            DrawBlackLine(x0 + width, y0, x0 + width - 5, y0 + 5);
            DrawBlackLine(x0, y0 - height, x0 - 5, y0 - height + 5);
            DrawBlackLine(x0, y0 - height, x0 + 5, y0 - height + 5);

            for (float i = pointsInSegment * step; i < width - 5; i += pointsInSegment * step)
            {
                float x = x0 + i;
                x = (float)Math.Round(x, 1);
                DrawBlackLine(x, y0 - 5, x, y0 + 5);
                float number = i / pointsInSegment;

                DrawNumberX(i / pointsInSegment, pointsInSegment);
            }
            for (float i = -pointsInSegment * step; i > -width; i -= pointsInSegment * step)
            {
                float x = x0 + i;
                x = (float)Math.Round(x, 1);
                DrawBlackLine(x, y0 - 5, x, y0 + 5);
                DrawNumberX(i / pointsInSegment, pointsInSegment);
            }

            for (float i = pointsInSegment * step; i < height; i += pointsInSegment * step)
            {
                float y = (float)y0 + i;
                y = (float)Math.Round(y, 1);
                DrawBlackLine(x0 - 5, y, x0 + 5, y);
                DrawNumberY(i / pointsInSegment, pointsInSegment);
            }
            for (float i = -pointsInSegment * step; i > -height + 5; i -= pointsInSegment * step)
            {
                float y = (float)y0 + i;
                y = (float)Math.Round(y, 1);
                DrawBlackLine(x0 - 5, y, x0 + 5, y);
                DrawNumberY(i / pointsInSegment, pointsInSegment);
            }

            TextBlock textBlock = new TextBlock();
            textBlock.Text = "0";
            textBlock.FontSize = 10;
            Canvas.SetLeft(textBlock, x0 - 9);
            Canvas.SetTop(textBlock, y0 + 2);
            canvas.Children.Add(textBlock);
        }

        private void buttonDraw_Click(object sender, RoutedEventArgs e)
        {
            scale = (float)scaleChangeLabel.Tag;
            canvas.Children.Clear();
            float step = 1;
            if (scale == 0.1f)
            {
                step = 10;
            }
            else if (scale < 0.7f)
            {
                step = 5;
            }
            else if (scale < 2f)
            {
                step = 1f;
            }
            else if (scale < 3f)
            {
                step = 0.5f;
            }
            else
            {
                step = 0.2f;
            }

            pointsInSegment = (int)(width / 10 * scale);
            DrawSystem(step);

            ACurve curve = (ACurve)curvesComboBox.SelectedItem;
            if (curve != null)
            {
                DrawCurve(curve);
            }
        }

        private void DrawCurve(ACurve curve)
        {
            List<PointF>[] points = curve.GetPoints(pointsInSegment);

            List<PointF> pointsNegative = points[0];
            PointCollection negative = new PointCollection();
            foreach (var temp in pointsNegative)
            {
                negative.Add(new System.Windows.Point(temp.X + x0, temp.Y + y0));
            }
            Polyline polylineNegative = new Polyline();
            polylineNegative.Points = negative;
            polylineNegative.Stroke = System.Windows.Media.Brushes.Black;
            polylineNegative.StrokeThickness = 1;
            canvas.Children.Add(polylineNegative);

            List<PointF> pointsPositive = points[1];
            PointCollection positive = new PointCollection();
            foreach (var temp in pointsPositive)
            {
                positive.Add(new System.Windows.Point(temp.X + x0, temp.Y + y0));
            }
            Polyline polylinePositive = new Polyline();
            polylinePositive.Points = positive;
            polylinePositive.Stroke = System.Windows.Media.Brushes.Black;
            polylinePositive.StrokeThickness = 1;
            canvas.Children.Add(polylinePositive);
        }
    }
}
