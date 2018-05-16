using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace WinFormsTechnology
{
    public partial class MainForm : Form
    {
        private Graphics graphics;
        private Pen pen;

        public MainForm()
        {
            InitializeComponent();

            pen = new Pen(Color.Black);
            graphics = PictureBox.CreateGraphics();
            graphics.SmoothingMode = SmoothingMode.AntiAlias;

            Model model = new Model(PictureBox, graphics);

            // add available curves
            CurveListComboBox.Items.AddRange(model.Curves);

            // events
            CurveListComboBox.SelectedIndexChanged += new EventHandler(model.ComboBoxSelectedIndexChanged);
            BtnScaleUp.Click += new EventHandler(model.ScaleUp);
            BtnScaleDown.Click += new EventHandler(model.ScaleDown);

            // events
            model.EnableScaleDownBtn += (bool x) => BtnScaleDown.Enabled = x;
            model.EnableScaleUpBtn += (bool x) => BtnScaleUp.Enabled = x;
            model.SetPenWidth += (float x) => pen.Width = x;

            model.DrawCurve += (PointF[] points) => graphics.DrawCurve(pen, points);
            model.DrawEllipse += (float x, float y, float width, float height) => graphics.DrawEllipse(pen, x, y, width, height);
            model.DrawLine += (float x1, float y1, float x2, float y2) => graphics.DrawLine(pen, x1, y1, x2, y2);

            model.Clear += Clear;
            model.DrawAxis += DrawAxis;
        }

        private void Clear()
        {
            graphics.Clear(Color.White);
        }

        private void DrawAxis(float halfWidth, float halfHeight)
        {
            graphics.DrawLine(pen, 0, -halfHeight, 0, halfHeight);
            graphics.DrawLine(pen, -halfWidth, 0, halfWidth, 0);
        }
    }
}
