using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

using AlgebraicCurveLibrary;
using AlgebraicCurveLibrary.Exapmles;

namespace WinFormsTechnology
{
    internal class Model
    {
        public delegate void Enable(bool enabled);
        public delegate void SetFloat(float value);

        public delegate void CurveDrawingHandler(PointF[] points);
        public delegate void EllipseDrawingHandler(float x, float y, float width, float height);
        public delegate void LineDrawingHandler(float x1, float y1, float x2, float y2);

        public delegate void ClearingHandler();
        public delegate void AxisDrawingHandler(float halfWidth, float halfHeight);

        public event Enable EnableScaleUpBtn;
        public event Enable EnableScaleDownBtn;
        public event SetFloat SetPenWidth;

        public event CurveDrawingHandler DrawCurve;
        public event EllipseDrawingHandler DrawEllipse;
        public event LineDrawingHandler DrawLine;
        public event ClearingHandler Clear;
        public event AxisDrawingHandler DrawAxis;

        #region constants
        private const float ScaleMultiplier = 1.25f;
        private const int MaxScalePower = 15;

        private readonly float MaxScale;
        private readonly float MinScale;
        #endregion

        #region fields
        private List<CurveBase> curves;
        private CurveBase selected;

        private PictureBox pictureBox;
        private Graphics graphics;

        private Matrix originalTransform;
        private float scale;
        #endregion

        #region properties
        /// <summary>
        /// Array of all curves
        /// </summary>
        public CurveBase[] Curves
        {
            get
            {
                return curves.ToArray();
            }
        }

        /// <summary>
        /// PictureBox half width
        /// </summary>
        private float HalfBoxWidth
        {
            get
            {
                return (pictureBox.Width) / 2;
            }
        }

        /// <summary>
        /// PictureBox half height
        /// </summary>
        private float HalfBoxHeight
        {
            get
            {
                return (pictureBox.Height) / 2;
            }
        }

        /// <summary>
        /// Scaled PictureBox half width
        /// </summary>
        private float ScaledHalfBoxWidth
        {
            get
            {
                return HalfBoxWidth / scale;
            }
        }

        /// <summary>
        /// Scaled PictureBox half height
        /// </summary>
        private float ScaledHalfBoxHeight
        {
            get
            {
                return HalfBoxHeight / scale;
            }
        }
        #endregion

        public Model(PictureBox pictureBox, Graphics graphics)
        {
            this.pictureBox = pictureBox;
            this.graphics = graphics;

            curves = new List<CurveBase>();

            curves.Add(new Line());
            curves.Add(new Circle());
            curves.Add(new Ellipse());
            curves.Add(new Parabola());
            curves.Add(new Hyperbola());

            graphics.TranslateTransform(HalfBoxWidth, HalfBoxHeight);
            originalTransform = graphics.Transform.Clone();

            scale = 1f;
            MaxScale = (float)Math.Pow(ScaleMultiplier, MaxScalePower);
            MinScale = (float)Math.Pow(ScaleMultiplier, -MaxScalePower);
        }

        /// <summary>
        /// ComboBox event
        /// </summary>
        public void ComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            selected = (CurveBase)((ComboBox)sender).SelectedItem;
            Draw();
        }

        #region drawing
        /// <summary>
        /// Draws selected curve
        /// </summary>
        private void Draw()
        {
            if (selected == null)
            {
                return;
            }

            Clear();
            DrawAxis(ScaledHalfBoxWidth, ScaledHalfBoxHeight);

            switch (selected.Type)
            {
                case DrawableCurveType.Curve:
                    {
                        Curve curve = (Curve)selected;
                        Draw(curve);

                        break;
                    }
                case DrawableCurveType.Ellipse:
                    {
                        Ellipse ellipse = (Ellipse)selected;
                        Draw(ellipse);

                        break;
                    }
                case DrawableCurveType.Line:
                    {
                        Line line = (Line)selected;
                        Draw(line);

                        break;
                    }
            }
        }

        private void Draw(Curve curve)
        {
            Vector2 ul = new Vector2(- ScaledHalfBoxWidth, ScaledHalfBoxHeight);
            Vector2 lr = new Vector2(ScaledHalfBoxWidth, -ScaledHalfBoxHeight);

            PointF[][] points = curve.GetDrawingPoints(ul, lr);

            // foreach part
            for (int i = 0; i < points.Length; i++)
            {
                if (points[i].Length < 2)
                {
                    continue;
                }

                DrawCurve(points[i]);
            }
        }

        private void Draw(Ellipse ellipse)
        {
            // center offset
            float offsetX = -ellipse.SemiMajorAxis / 2;
            float offsetY = -ellipse.SemiMinorAxis / 2;

            DrawEllipse(offsetX, offsetY, ellipse.SemiMajorAxis, ellipse.SemiMinorAxis);
        }

        private void Draw(Line line)
        {
            // stretch line
            float length = 2 * (new Vector2(ScaledHalfBoxWidth, ScaledHalfBoxHeight)).Length;
            Vector2 lineDir = line.Direction * length;

            DrawLine(-lineDir.X, lineDir.Y, lineDir.X, -lineDir.Y);
        }
        #endregion

        #region scaling
        /// <summary>
        /// Scaling up event
        /// </summary>
        public void ScaleUp(object sender, EventArgs e)
        {
            if (scale <= MinScale)
            {
                EnableScaleDownBtn(true);
            }

            ScaleCurves(ScaleMultiplier);

            if (scale >= MaxScale)
            {
                EnableScaleUpBtn(false);
            }
        }

        /// <summary>
        /// Scaling down event
        /// </summary>
        public void ScaleDown(object sender, EventArgs e)
        {
            if (scale >= MaxScale)
            {
                EnableScaleUpBtn(true);
            }

            ScaleCurves(1 / ScaleMultiplier);

            if (scale <= MinScale)
            {
                EnableScaleDownBtn(false);
            }
        }

        private void ScaleCurves(float scale)
        {
            this.scale *= scale;

            Matrix newTransform = originalTransform.Clone();
            newTransform.Scale(this.scale, this.scale);

            graphics.Transform = newTransform;
            SetPenWidth(1 / this.scale);

            Draw();
        }
        #endregion
    }
}
