using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using CurvesMath;
using CurvesMath.Curves;

namespace CurvesWinForms
{
    public partial class CurvesWindow : Form
    {
        private ACurve _choosenCurve;

        private readonly Graphics _renderer;
        private readonly Pen _pen;

        private int _scale;

        private int Scale
        {
            get { return _scale; }
            set
            {
                if (value >= 50)
                {
                    _scale = 50;
                    return;
                }

                if (value <= 2)
                {
                    _scale = 2;
                    return;
                }

                _scale = value;
            }
        }


        public CurvesWindow()
        {
            InitializeComponent();
            Scale = 20;
            _renderer = CreateGraphics();
            _pen = new Pen(Color.Red, 2);
            MouseWheel += delegate(object sender, MouseEventArgs args) {
                Scale += args.Delta < 0 ? Scale / 10 : -Scale / 10;
                if (_choosenCurve != null)
                {
                    DrawGraph();
                }
            };
        }
        
        private void CurvesWindow_Load(object sender, EventArgs e)
        {
            var comboBox = new ComboBox
            {
                Top = 5,
                Width = ClientSize.Width,
                Items =
                    {new EllipseCurve(9, 4), new HyperbolaCurve(3, 2), new ParabolaCurve(2)},
                DropDownStyle = ComboBoxStyle.DropDownList
            };
            
            comboBox.SelectedIndexChanged += delegate
            {
                _choosenCurve = comboBox.SelectedItem as ACurve;
                if (_choosenCurve != null)
                {
                    DrawGraph();
                }
                
            };

            Controls.Add(comboBox);
        }

        private void DrawGraph()
        {
            _renderer.Clear(BackColor);
            DrawCoordinateSystem();
            double step = 1.0/Scale/Math.Sqrt(Scale);
            _choosenCurve.RecalculateIntervals(Size.Width/2/Scale);

            foreach (var currentInterval in _choosenCurve.CurvesDefinedIntervals)
            {
                double i = currentInterval.Begin;
                for (; i < currentInterval.End - step; i += step)
                {
                    List<System.Windows.Point> solutions = _choosenCurve.FindSolutions(i);
                    List<System.Windows.Point> secondSolutions = _choosenCurve.FindSolutions(i + step);
                    for (int k = 0; k < solutions.Count && (solutions.Count == secondSolutions.Count); ++k)
                    {
                        _renderer.DrawLine(_pen,
                            (float) ConvertPoint(solutions[k]).X, 
                            (float) ConvertPoint(solutions[k]).Y,
                            (float) (ConvertPoint(secondSolutions[k]).X), 
                            (float) ConvertPoint(secondSolutions[k]).Y);
                    }
                }

                List<System.Windows.Point> nearTheEndSoulutions = _choosenCurve.FindSolutions(i);
                List<System.Windows.Point> endIntervalSolution = _choosenCurve.FindSolutions(currentInterval.End);
                for (int k = 0;
                    k < nearTheEndSoulutions.Count && (nearTheEndSoulutions.Count == endIntervalSolution.Count);
                    ++k)
                {
                    _renderer.DrawLine(_pen,
                        (float) ConvertPoint(nearTheEndSoulutions[k]).X,
                        (float) ConvertPoint(nearTheEndSoulutions[k]).Y,
                        (float) (ConvertPoint(endIntervalSolution[k]).X),
                        (float) ConvertPoint(endIntervalSolution[k]).Y);
                }
            }
        }

        private void DrawCoordinateSystem()
        {
            var tmpPen = new Pen(Color.Black, 1);
            _renderer.DrawLine(tmpPen, 0, ClientSize.Height / 2, ClientSize.Width, ClientSize.Height / 2);
            _renderer.DrawLine(tmpPen, ClientSize.Width / 2, 0, ClientSize.Width / 2, ClientSize.Height);

            for (int i = 0; i < ClientSize.Width / 2; i += Scale)
            {
                _renderer.DrawLine(tmpPen, ClientSize.Width / 2 + i, ClientSize.Height / 2 + 2, ClientSize.Width / 2 + i, ClientSize.Height / 2 - 2);
                _renderer.DrawLine(tmpPen, ClientSize.Width / 2 - i, ClientSize.Height / 2 + 2, ClientSize.Width / 2 - i, ClientSize.Height / 2 - 2);
            }

            for (int i = 0; i < ClientSize.Height / 2; i += Scale)
            {
                _renderer.DrawLine(tmpPen, ClientSize.Width / 2 - 2, ClientSize.Height / 2 + i, ClientSize.Width / 2 + 2, ClientSize.Height / 2 + i);
                _renderer.DrawLine(tmpPen, ClientSize.Width / 2 - 2, ClientSize.Height / 2 - i, ClientSize.Width / 2 + 2, ClientSize.Height / 2 - i);
            }
        }

        private System.Windows.Point ConvertPoint(System.Windows.Point input)
        {
           
            return new System.Windows.Point{X = ClientSize.Width / 2 + input.X * Scale, Y = ClientSize.Height / 2 + input.Y * Scale};
        }
    }
}