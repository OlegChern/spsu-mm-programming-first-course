using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using Curves;

namespace Task6.Curves
{
    public partial class CurveForm : Form
    {
        private Graphics graphic;

        private float width;

        private float height;

        private float scale;

        private int pointsInSegment;

        public CurveForm()
        {
            InitializeComponent();

            graphic = CreateGraphics();
            width = ClientSize.Width / 2 - 5;
            height = ClientSize.Height / 2 - 5;
            graphic.TranslateTransform(width + 5, height + 5);
            scale = 1f;
            pointsInSegment = (int)(width / 16 * scale);

            Small_Increase.Tag = 0.1f;
            Large_Increase.Tag = 1f;
            Small_Decrease.Tag = -0.1f;
            Large_Decrease.Tag = -1f;
            ScaleChangeLabel.Tag = 1f;

            comboBoxCurves.Items.AddRange(new ACurve[] { new Ellipse(1, 1, -width, width),
                new Ellipse(3, 0.5f, -width, width), new Hyperbola(1, 1, -width, width),
                new Hyperbola(5, 2, -width, width), new Parabola(0.2f, -width, width),
                new Parabola(-5, -width, width)});
        }

        private void DrawSystem(float step)
        {
            graphic.DrawLine(Pens.Black, -width, 0, width, 0);
            graphic.DrawLine(Pens.Black, 0, height, 0, -height);

            for (float i = pointsInSegment * step; i < width - 5; i += pointsInSegment * step)
            {
                i = (float)Math.Round(i, 1);
                graphic.DrawLine(Pens.Black, i, -5, i, 5);
                DrawNumberX(i / pointsInSegment, graphic, pointsInSegment);
            }
            for (float i = -pointsInSegment * step; i > -width; i -= pointsInSegment * step)
            {
                i = (float)Math.Round(i, 1);
                graphic.DrawLine(Pens.Black, i, -5, i, 5);
                DrawNumberX(i / pointsInSegment, graphic, pointsInSegment);
            }
            graphic.DrawLine(Pens.Black, width, 0, width - 5, -5);
            graphic.DrawLine(Pens.Black, width, 0, width - 5, 5);

            for (float i = pointsInSegment * step; i < height; i += pointsInSegment * step)
            {
                i = (float)Math.Round(i, 1);
                graphic.DrawLine(Pens.Black, -5, i, 5, i);
                DrawNumberY(i / pointsInSegment, graphic, pointsInSegment);
            }
            for (float i = -pointsInSegment * step; i > -height + 5; i -= pointsInSegment * step)
            {
                i = (float)Math.Round(i, 1);
                graphic.DrawLine(Pens.Black, -5, i, 5, i);
                DrawNumberY(i / pointsInSegment, graphic, pointsInSegment);
            }
            graphic.DrawLine(Pens.Black, 0, -height, -5, -height + 5);
            graphic.DrawLine(Pens.Black, 0, -height, 5, -height + 5);

            graphic.FillEllipse(Brushes.Black, new Rectangle(-2, -2, 4, 4));
            var font = new Font(Font.FontFamily, 6);
            var size = graphic.MeasureString("0", font);
            var rectangle = new RectangleF(new PointF(-size.Width - 1, 3), size);
            graphic.DrawString("0", font, Brushes.Black, rectangle);
        }

        private void DrawNumberX(float number, Graphics g, int pixelsInSegment)
        {
            number = (float)Math.Round(number, 1);
            var font = new Font(Font.FontFamily, 6);
            var size = g.MeasureString(number.ToString(), font);
            var rectangle = new RectangleF(new PointF(number * pixelsInSegment - size.Width / 2, 5 + 1), size);
            g.DrawString(number.ToString(), font, Brushes.Black, rectangle);
        }

        private void DrawNumberY(float number, Graphics g, int pixelsInSegment)
        {
            number = (float)Math.Round(number, 1);
            var font = new Font(Font.FontFamily, 6);
            var size = g.MeasureString((-number).ToString(), font);
            var rectangle = new RectangleF(new PointF(-5 - size.Width, number * pixelsInSegment - size.Height / 2), size);
            g.DrawString((-number).ToString(), font, Brushes.Black, rectangle);
        }

        private void DrawCurve(ACurve curve)
        {
            List<PointF>[] points = curve.GetPoints(pointsInSegment);

            List<PointF> pointsNegative = points[0];
            pointsNegative.ToArray();
            graphic.DrawCurve(Pens.Black, pointsNegative.ToArray());

            List<PointF> pointsPositive = points[1];
            pointsPositive.ToArray();
            graphic.DrawCurve(Pens.Black, pointsPositive.ToArray());
        }

        private void buildButton_Click(object sender, EventArgs e)
        {
            scale = (float)ScaleChangeLabel.Tag;
            graphic.Clear(BackColor);
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

            pointsInSegment = (int)(width / 16 * scale);
            DrawSystem(step);

            ACurve curve = (ACurve)comboBoxCurves.SelectedItem;
            if(curve != null)
            {
                DrawCurve(curve);
            }
        }

        private void buttonIncDec_Click(object sender, EventArgs e)
        {
            float newTag = (float)ScaleChangeLabel.Tag + (float)((sender as Button).Tag);
            ScaleChangeLabel.Tag = (float)Math.Round(newTag, 1);
            if (((float)ScaleChangeLabel.Tag > 0f) && ((float)ScaleChangeLabel.Tag < 5f))
            {
                ScaleChangeLabel.Text = ScaleChangeLabel.Tag.ToString();
            }
            else
            {
                ScaleChangeLabel.Tag = (float)ScaleChangeLabel.Tag - (float)((sender as Button).Tag);
            }
        }
    }
}
