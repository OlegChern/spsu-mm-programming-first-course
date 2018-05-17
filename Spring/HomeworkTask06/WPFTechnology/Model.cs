using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections.ObjectModel;

using AlgebraicCurveLibrary;
using AlgebraicCurveLibrary.Exapmles;
using System.Windows.Media;

namespace WPFTechnology
{
    using System.Windows.Controls;
    using WPoint = System.Windows.Point;

    public class Model
    {
        public delegate void Enable(bool enabled);
        public delegate void DrawHandler(Geometry geometry);

        public event Enable EnableScaleUpBtn;
        public event Enable EnableScaleDownBtn;
        public event DrawHandler DrawGeometry;

        #region constants
        const float ScaleMultiplier = 1.25f;
        const int MaxScalePower = 10;
        const int MinScalePower = -10;
        #endregion

        #region fields
        private Canvas canvas;

        private List<CurveBase> curves;
        private CurveBase selected;

        private int scalePower;
        private float scale;
        #endregion

        #region properties
        public CurveBase[] CurvesArray
        {
            get
            {
                return curves.ToArray();
            }
        }

        public Canvas Canvas
        {
            get
            {
                return canvas;
            }
            set
            {
                canvas = value;
            }
        }

        private float CanvasHalfWidth
        {
            get
            {
                return (float)canvas.ActualWidth / 2;
            }
        }

        private float CanvasHalfHeight
        {
            get
            {
                return (float)canvas.ActualHeight / 2;
            }
        }
        #endregion

        public Model()
        {
            curves = new List<CurveBase>();

            curves.Add(new Line());
            curves.Add(new Circle(50));
            curves.Add(new Ellipse(130, 50));
            curves.Add(new Parabola());
            curves.Add(new Hyperbola());

            scale = 1;
        }

        public void SelectCurve(object curve)
        {
            selected = (CurveBase)curve;
            Draw();
        }

        public void Draw()
        {
            if (selected ==null)
            {
                return;
            }

            switch (selected.Type)
            {
                case DrawableCurveType.Line:
                    {
                        Line line = (Line)selected;

                        float length = 2 * (new Vector2(CanvasHalfWidth, CanvasHalfHeight)).Length;
                        Vector2 lineDir = line.Direction * length;

                        DrawGeometry(new LineGeometry(
                            new WPoint(-lineDir.X + CanvasHalfWidth, lineDir.Y + CanvasHalfWidth),
                            new WPoint(lineDir.X + CanvasHalfWidth, -lineDir.Y + CanvasHalfWidth)));

                        break;
                    }
                case DrawableCurveType.Ellipse:
                    {
                        Ellipse ellipse = (Ellipse)selected;
                        WPoint center = new WPoint(CanvasHalfWidth, CanvasHalfHeight);

                        DrawGeometry(new EllipseGeometry(center, ellipse.SemiMajorAxis * scale, ellipse.SemiMinorAxis * scale));
                        break;
                    }
                case DrawableCurveType.Curve:
                    {
                        PointF[][] points = ((Curve)selected).GetDrawingPoints(
                            new Vector2(-CanvasHalfWidth / scale, CanvasHalfHeight / scale),
                            new Vector2(CanvasHalfWidth / scale, -CanvasHalfHeight / scale));

                        PathFigure[] figures = new PathFigure[points.Length];

                        for (int i = 0; i < points.Length; i++)
                        {
                            figures[i] = new PathFigure();

                            List<WPoint> partPoints = new List<WPoint>();

                            if (points[i].Length > 0)
                            {
                                figures[i].StartPoint = Convert(points[i][0]);
                            }

                            foreach (PointF point in points[i])
                            {
                                WPoint converted = Convert(point);
                                partPoints.Add(converted);
                            }

                            figures[i].Segments.Add(new PolyBezierSegment(partPoints, true));
                        }

                        DrawGeometry(new PathGeometry(figures));

                        break;
                    }
            }
        }

        private WPoint Convert(PointF point)
        {
            return new WPoint(point.X * scale + CanvasHalfWidth, point.Y * scale + CanvasHalfHeight);
        }

        #region scaling
        /// <summary>
        /// Scaling up event
        /// </summary>
        public void ScaleUp(object sender, EventArgs e)
        {
            if (scalePower <= MinScalePower)
            {
                EnableScaleDownBtn(true);
            }

            scalePower++;
            scale *= ScaleMultiplier;

            if (scalePower >= MaxScalePower)
            {
                EnableScaleUpBtn(false);
            }

            Draw();
        }

        /// <summary>
        /// Scaling down event
        /// </summary>
        public void ScaleDown(object sender, EventArgs e)
        {
            if (scalePower >= MaxScalePower)
            {
                EnableScaleUpBtn(true);
            }

            scalePower--;
            scale /= ScaleMultiplier;

            if (scalePower <= MinScalePower)
            {
                EnableScaleDownBtn(false);
            }

            Draw();
        }
        #endregion
    }
}