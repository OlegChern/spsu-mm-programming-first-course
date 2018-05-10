using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace WinFormsTechnology
{
    public partial class MainForm : Form
    {
        private Model model;
        private Controller controller;

        private Graphics graphics;
        private Pen pen;

        #region initializing
        public MainForm()
        {
            InitializeComponent();

            pen = new Pen(Color.Black);
            graphics = PictureBox.CreateGraphics();
            graphics.SmoothingMode = SmoothingMode.AntiAlias;

            model = new Model(this, graphics);
            controller = new Controller(model);

            CurveListComboBox.Items.AddRange(model.Curves);

            this.CurveListComboBox.SelectedIndexChanged += new System.EventHandler(controller.ComboBoxSelectedIndexChanged);
            this.BtnScaleUp.Click += new System.EventHandler(controller.BtnScaleUpClick);
            this.BtnScaleDown.Click += new System.EventHandler(controller.BtnScaleDownClick);

            model.EnableScaleDownBtn += (bool x) => BtnScaleDown.Enabled = x;
            model.EnableScaleUpBtn += (bool x) => BtnScaleUp.Enabled = x;
            model.SetPenWidth += (float x) => pen.Width = x;
        }
        #endregion

        #region drawing
        public void DrawCurve(PointF[] points)
        {
            graphics.DrawCurve(pen, points);
        }

        public void DrawEllipse(float x, float y, float width, float height)
        {
            graphics.DrawEllipse(pen, x, y, width, height);
        }

        public void DrawLine(float x1, float y1, float x2, float y2)
        {
            graphics.DrawLine(pen, x1, y1, x2, y2);
        }

        public void DrawAxis(float width, float height)
        {
            graphics.DrawLine(pen, 0, -height, 0, height);
            graphics.DrawLine(pen, -width, 0, width, 0);
        }

        public void Clear()
        {
            graphics.Clear(Color.White);
        }
        #endregion
    }
}
