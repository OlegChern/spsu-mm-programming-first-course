using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using CurvesMath;
using CurvesMath.Curves;

namespace CurvesWPF
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Fields

        private ViewModel ViewModel;

        private double _scale;

        private double Scale
        {
            get { return _scale; }
            set
            {
                if (value >= 200)
                {
                    _scale = 200;
                    return;
                }

                if (value <= 0.3)
                {
                    _scale = 0.3;
                    return;
                }

                _scale = value;
            }
        }
        #endregion

        public MainWindow()
        {
            InitializeComponent();
            ViewModel = new ViewModel();
            Scale = 15;
        }

        #region Event Handlers
        private void CurveChoosed(object sender, SelectionChangedEventArgs e)
        {
            if (ViewModel.ChoosenCurve != null)
            {
                DrawGraph();
            }
            DrawGraph();

        }

        private void ScaleChangedByMouseWheel(object sender, MouseWheelEventArgs e)
        {
            Scale += e.Delta < 0 ? Scale / 10 : -Scale / 10;
            DrawCoordinateSystem(Scale);
            if (ViewModel.ChoosenCurve != null)
            {
                DrawGraph();
            }
        }

        private void RewriteCoordinateSystemAfterResize(object sender,  SizeChangedEventArgs sizeChangedEventArgs)
        {
            DrawCoordinateSystem(Scale);
            if (ViewModel.ChoosenCurve != null)
            {
                DrawGraph();
            }
        }
        #endregion

        #region Drawing Methods
        private void DrawCoordinateSystem(double scale)
        {
            double centerCoordinateX = Rendering.ActualWidth / 2;
            double centerCoordinateY = Rendering.ActualHeight / 2;


            PositiveHorizontalDashes.Children.Clear();
            NegativeVerticalDashes.Children.Clear();
            NegativeHorizontalDashes.Children.Clear();
            PositiveVerticalDashes.Children.Clear();

            //Set right places for canvas with Dashes
            Canvas.SetTop(PositiveHorizontalDashes, centerCoordinateY - 2.5);
            Canvas.SetLeft(PositiveHorizontalDashes, centerCoordinateX - 0.5);

            Canvas.SetTop(NegativeVerticalDashes, centerCoordinateY - 0.5);
            Canvas.SetLeft(NegativeVerticalDashes, centerCoordinateX - 2.5);

            Canvas.SetTop(NegativeHorizontalDashes, centerCoordinateY - 2.5);

            Canvas.SetLeft(PositiveVerticalDashes, centerCoordinateX - 2.5);

            //Draw Axes of coordinates
            AxesOfCoordinates.Children.Clear();

            Rectangle tmpOX = new Rectangle {Height = 0.3, Width = Rendering.ActualWidth, Fill = Brushes.Black};
            Canvas.SetTop(tmpOX, centerCoordinateY - tmpOX.Height / 2);
            AxesOfCoordinates.Children.Add(tmpOX);

            Rectangle tmpOY = new Rectangle {Width = 0.3, Height = Rendering.ActualHeight, Fill = Brushes.Black};
            Canvas.SetLeft(tmpOY, centerCoordinateX - tmpOY.Width / 2);
            AxesOfCoordinates.Children.Add(tmpOY);


            //Rendering Right Line of Dashes
            for (double i = scale - 0.5; i < centerCoordinateX; i += scale)
            {
                Rectangle dash = new Rectangle {Height = 5, Width = 1, Fill = Brushes.Black};
                Canvas.SetLeft(dash, i);
                PositiveHorizontalDashes.Children.Add(dash);
            }

            //Rendering Bottom Line of Dashes
            for (double i = scale - 0.5; i < centerCoordinateY; i += scale)
            {
                Rectangle dash = new Rectangle {Height = 1, Width = 5, Fill = Brushes.Black};
                Canvas.SetTop(dash, i);
                NegativeVerticalDashes.Children.Add(dash);
            }

            //Rendering Left Line of Dashes

            for (double i = centerCoordinateX - scale + 0.5; i > 0; i -= scale)
            {
                Rectangle dash = new Rectangle {Height = 5, Width = 1, Fill = Brushes.Black};
                Canvas.SetLeft(dash, i);
                NegativeHorizontalDashes.Children.Add(dash);
            }

            //Rendering Top Line of Dashes
            for (double i = centerCoordinateY - scale + 0.5; i > 0; i -= scale)
            {
                Rectangle dash = new Rectangle {Height = 1, Width = 5, Fill = Brushes.Black};
                Canvas.SetTop(dash, i);
                PositiveVerticalDashes.Children.Add(dash);
            }
        }

        private void DrawGraph()
        {
            
            double step = 1 / Scale / Math.Sqrt(Scale);
            ViewModel.ChoosenCurve.RecalculateIntervals(Rendering.ActualWidth / 2 / Scale);

            PathGeometry graphGeometry = new PathGeometry();
            
            List<PolyLineSegment> segments = new List<PolyLineSegment>();

            for (byte i = 0; i < ViewModel.ChoosenCurve.MaxNumberOfSolutions * ViewModel.ChoosenCurve.CurvesDefinedIntervals.Count; ++i)
            {
                segments.Add(new PolyLineSegment());
            }

            for (int ind = 0; ind < ViewModel.ChoosenCurve.CurvesDefinedIntervals.Count; ++ind)
            {
                Interval currentInterval = ViewModel.ChoosenCurve.CurvesDefinedIntervals[ind];
                for (double i = currentInterval.Begin; i < currentInterval.End; i += step)
                {
                    List<Point> solutions = ViewModel.ChoosenCurve.FindSolutions(i);
                    if (solutions.Count != 1)
                    {
                        for (int k = 0; k < solutions.Count; ++k)
                        {
                            segments[ind * ViewModel.ChoosenCurve.MaxNumberOfSolutions + k].Points.Add(ConvertPoint(solutions[k]));
                        }
                    }

                    else
                    {
                        for (int k = 0; k < ViewModel.ChoosenCurve.MaxNumberOfSolutions; ++k)
                        {
                            segments[ind * ViewModel.ChoosenCurve.MaxNumberOfSolutions + k].Points.Add(ConvertPoint(solutions[0]));
                        }
                    }
                }
            }

            foreach (var interval in ViewModel.ChoosenCurve.CurvesDefinedIntervals)
            {
                for (byte i = 0; i < segments.Count; ++i)
                {
                    var tmpPathFigure = new PathFigure();
                    tmpPathFigure.StartPoint = segments[i].Points.First();
                    tmpPathFigure.Segments.Add(segments[i]);
                    graphGeometry.Figures.Add(tmpPathFigure);
                }
            }

            Graph.Data = graphGeometry;
        }
        #endregion

        private Point ConvertPoint(Point input)
        {
            input.X = Rendering.ActualWidth / 2 + input.X * Scale;
            input.Y = Rendering.ActualHeight / 2 + input.Y * Scale;
            return input;
        }
    }
}