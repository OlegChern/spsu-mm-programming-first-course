using System;
using System.Collections.Generic;
using System.Drawing;
using AlgebraicCurveLibrary;
using AlgebraicCurveLibrary.Exapmles;

namespace WinFormsTechnology
{
    internal class Model
    {
        private List<CurveBase> curves;
        private CurveBase selected;

        /// <summary>
        /// Current curve to draw
        /// </summary>
        internal object Selected
        {
            set
            {
                selected = (CurveBase)value;
            }
        }

        internal Model()
        {
            curves = new List<CurveBase>();

            curves.Add(new Line());
            curves.Add(new Circle());
            curves.Add(new Ellipse());
            curves.Add(new Parabola());
            curves.Add(new Hyperbola());

            MainForm.Instance.AddComboBoxItems(curves.ToArray());
        }

        /// <summary>
        /// Draws selected curve
        /// </summary>
        internal void Draw()
        {
            MainForm.Instance.Clear();

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
            Vector2 ul = new Vector2(- MainForm.ScaledHalfBoxWidth, MainForm.ScaledHalfBoxHeight);
            Vector2 lr = new Vector2(MainForm.ScaledHalfBoxWidth, -MainForm.ScaledHalfBoxHeight);

            PointF[][] points = curve.GetDrawingPoints(ul, lr);

            // foreach part
            for (int i = 0; i < points.Length; i++)
            {
                if (points[i].Length < 2)
                {
                    continue;
                }

                MainForm.Instance.DrawCurve(points[i]);
            }
        }

        private void Draw(Ellipse ellipse)
        {
            // center offset
            float offsetX = -ellipse.SemiMajorAxis / 2;
            float offsetY = -ellipse.SemiMinorAxis / 2;

            MainForm.Instance.DrawEllipse(offsetX, offsetY, ellipse.SemiMajorAxis, ellipse.SemiMinorAxis);
        }

        private void Draw(Line line)
        {
            // stretch line
            float length = 2 * (new Vector2(MainForm.ScaledHalfBoxWidth, MainForm.ScaledHalfBoxHeight)).Length;
            Vector2 lineDir = line.Direction * length;

            MainForm.Instance.DrawLine(-lineDir.X, lineDir.Y, lineDir.X, -lineDir.Y);
        }
    }
}
