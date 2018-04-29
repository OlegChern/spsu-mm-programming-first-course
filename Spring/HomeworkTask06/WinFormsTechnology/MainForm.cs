using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using AlgebraicCurveLibrary;
using AlgebraicCurveLibrary.Exapmles;

namespace WinFormsTechnology
{
    public partial class MainForm : Form
    {
        #region fields
        private List<CurveBase> curves;
        private CurveBase selected;
        private Graphics graphics;
        private Pen pen;

        private Matrix originalTransform;
        private float scale;
        #endregion

        #region properties
        private float HalfBoxWidth
        {
            get
            {
                return PictureBox.Size.Width / 2;
            }
        }
        private float HalfBoxHeight
        {
            get
            {
                return PictureBox.Size.Height / 2;
            }
        }

        private float ScaledHalfBoxWidth
        {
            get
            {
                return HalfBoxWidth / scale;
            }
        }
        private float ScaledHalfBoxHeight
        {
            get
            {
                return HalfBoxHeight / scale;
            }
        }
        #endregion

        #region initializing
        public MainForm()
        {
            curves = new List<CurveBase>();
            AddCurves();

            string[] names = new string[curves.Count];

            for (int i = 0; i < curves.Count; i++)
            {
                names[i] = curves[i].Name;
            }

            InitializeComponent();
            CurveListComboBox.Items.AddRange(curves.ToArray());

            pen = new Pen(Color.Black);
            graphics = PictureBox.CreateGraphics();
            graphics.SmoothingMode = SmoothingMode.AntiAlias;

            originalTransform = graphics.Transform.Clone();

            graphics.TranslateTransform(HalfBoxWidth, HalfBoxHeight);
            scale = 1f;
        }

        private void AddCurves()
        {
            curves.Add(new Line());
            curves.Add(new Circle());
            curves.Add(new Ellipse());
            curves.Add(new Parabola());
            curves.Add(new Hyperbola());
        }
        #endregion

        #region combobox
        private void CurveListComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox comboBox = (ComboBox)sender;
            selected = (CurveBase)comboBox.SelectedItem;

            Draw();
        }
        #endregion

        #region drawing
        private void Draw()
        {
            Clear();

            if (selected == null)
            {
                return;
            }

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
            Vector2 ul = new Vector2(-ScaledHalfBoxWidth, ScaledHalfBoxHeight);
            Vector2 lr = new Vector2(ScaledHalfBoxWidth, -ScaledHalfBoxHeight);

            PointF[][] points = curve.GetDrawingPoints(ul, lr, 5 / scale);

            // foreach part
            for (int i = 0; i < points.Length; i++)
            {
                if (points[i].Length < 2)
                {
                    continue;
                }

                graphics.DrawCurve(pen, points[i]);
            }
        }

        private void Draw(Ellipse ellipse)
        {
            // center offset
            float offsetX = -ellipse.SemiMajorAxis / 2;
            float offsetY = -ellipse.SemiMinorAxis / 2;

            graphics.DrawEllipse(pen, offsetX, offsetY, ellipse.SemiMajorAxis, ellipse.SemiMinorAxis);
        }

        private void Draw(Line line)
        {
            // stretch line
            float length = (new Vector2(ScaledHalfBoxWidth * 2, ScaledHalfBoxHeight * 2)).Length;
            Vector2 lineDir = line.Direction * length;

            // just draw 2 lines
            // inverted y axis because coords calculated from the up
            graphics.DrawLine(pen, 0, 0, lineDir.X, -lineDir.Y);
            graphics.DrawLine(pen, 0, 0, -lineDir.X, lineDir.Y);
        }

        private void DrawAxis()
        {
            graphics.DrawLine(pen, 0, -ScaledHalfBoxHeight, 0, ScaledHalfBoxHeight);
            graphics.DrawLine(pen, -ScaledHalfBoxWidth, 0, ScaledHalfBoxWidth, 0);
        }

        private void Clear()
        {
            graphics.Clear(Color.White);
            DrawAxis();
        }
        #endregion

        #region scaling
        private void BtnScaleDownClick(object sender, EventArgs e)
        {
            if (scale > 80f)
            {
                BtnScaleUp.Show();
            }

            ScaleCurves(0.8f);

            if (scale < 0.12f)
            {
                BtnScaleDown.Hide();
            }
        }

        private void BtnScaleUpClick(object sender, EventArgs e)
        {
            if (scale < 0.12f)
            {
                BtnScaleDown.Show();
            }

            ScaleCurves(1.25f);

            if (scale > 80f)
            {
                BtnScaleUp.Hide();
            }
        }

        private void ScaleCurves(float scale)
        {
            this.scale *= scale;

            pen.Width = 1 / this.scale;

            graphics.Transform = originalTransform.Clone();

            graphics.TranslateTransform(HalfBoxWidth, HalfBoxHeight);
            graphics.ScaleTransform(this.scale, this.scale);

            Draw();
        }
        #endregion
    }
}
