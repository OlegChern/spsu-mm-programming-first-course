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

        public event Enable EnableScaleUpBtn;
        public event Enable EnableScaleDownBtn;
        public event SetFloat SetPenWidth;

        #region constants
        private const float ScaleMultiplier = 1.25f;
        private const int MaxScalePower = 15;

        private readonly float MaxScale;
        private readonly float MinScale;
        #endregion

        #region fields
        private List<CurveBase> curves;
        private CurveBase selected;

        private Graphics graphics;
        private Matrix originalTransform;
        private float scale;

        private MainForm view;
        #endregion

        #region properties
        public CurveBase[] Curves
        {
            get
            {
                return curves.ToArray();
            }
        }

        private float HalfBoxWidth
        {
            get
            {
                return (view.PictureBox.Width) / 2;
            }
        }

        private float HalfBoxHeight
        {
            get
            {
                return (view.PictureBox.Height) / 2;
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

        public Model(MainForm view, Graphics graphics)
        {
            curves = new List<CurveBase>();

            curves.Add(new Line());
            curves.Add(new Circle());
            curves.Add(new Ellipse());
            curves.Add(new Parabola());
            curves.Add(new Hyperbola());

            this.view = view;
            this.graphics = graphics;
            this.graphics.TranslateTransform(HalfBoxWidth, HalfBoxHeight);

            originalTransform = this.graphics.Transform.Clone();

            scale = 1f;
            MaxScale = (float)Math.Pow(ScaleMultiplier, MaxScalePower);
            MinScale = (float)Math.Pow(ScaleMultiplier, -MaxScalePower);
        }

        #region drawing
        public void Draw(object selected)
        {
            this.selected = (CurveBase)selected;
            Draw();
        }

        /// <summary>
        /// Draws selected curve
        /// </summary>
        private void Draw()
        {
            if (selected == null)
            {
                return;
            }

            view.Clear();
            view.DrawAxis(ScaledHalfBoxWidth, ScaledHalfBoxHeight);

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

                view.DrawCurve(points[i]);
            }
        }

        private void Draw(Ellipse ellipse)
        {
            // center offset
            float offsetX = -ellipse.SemiMajorAxis / 2;
            float offsetY = -ellipse.SemiMinorAxis / 2;

            view.DrawEllipse(offsetX, offsetY, ellipse.SemiMajorAxis, ellipse.SemiMinorAxis);
        }

        private void Draw(Line line)
        {
            // stretch line
            float length = 2 * (new Vector2(ScaledHalfBoxWidth, ScaledHalfBoxHeight)).Length;
            Vector2 lineDir = line.Direction * length;

            view.DrawLine(-lineDir.X, lineDir.Y, lineDir.X, -lineDir.Y);
        }
        #endregion

        #region scaling
        public void ScaleUp()
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

        public void ScaleDown()
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
