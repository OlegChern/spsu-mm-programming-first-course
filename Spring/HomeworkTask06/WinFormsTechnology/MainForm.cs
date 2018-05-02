using System;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace WinFormsTechnology
{
    public partial class MainForm : Form
    {
        #region constants
        private const float ScaleMultiplier = 1.25f;
        private const int MaxScalePower = 15;

        private readonly float MaxScale;
        private readonly float MinScale;
        #endregion

        #region fields
        private static MainForm instance;
        private Model model;

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
                return (instance.PictureBox.Width) / 2;
            }
        }

        private float HalfBoxHeight
        {
            get
            {
                return (instance.PictureBox.Height) / 2;
            }
        }

        /// <summary>
        /// Scaled PictureBox half width
        /// </summary>
        internal static float ScaledHalfBoxWidth
        {
            get
            {
                return instance.HalfBoxWidth / instance.scale;
            }
        }

        /// <summary>
        /// Scaled PictureBox half height
        /// </summary>
        internal static float ScaledHalfBoxHeight
        {
            get
            {
                return instance.HalfBoxHeight / instance.scale;
            }
        }

        /// <summary>
        /// Instance of MainForm
        /// </summary>
        internal static MainForm Instance
        {
            get
            {
                return instance;
            }
        }
        #endregion

        #region initializing
        public MainForm()
        {
            instance = this;
            InitializeComponent();

            pen = new Pen(Color.Black);
            graphics = PictureBox.CreateGraphics();
            graphics.SmoothingMode = SmoothingMode.AntiAlias;

            originalTransform = graphics.Transform.Clone();

            graphics.TranslateTransform(HalfBoxWidth, HalfBoxHeight);
            scale = 1f;

            MaxScale = (float)Math.Pow(ScaleMultiplier, MaxScalePower);
            MinScale = (float)Math.Pow(ScaleMultiplier, -MaxScalePower);

            model = new Model();
        }

        /// <summary>
        /// Adds items to combobox
        /// </summary>
        /// <param name="arr"></param>
        internal void AddComboBoxItems(object[] arr)
        {
            CurveListComboBox.Items.AddRange(arr);
        }
        #endregion

        #region combobox event
        private void CurveListComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox comboBox = (ComboBox)sender;

            model.Selected = comboBox.SelectedItem;
            model.Draw();
        }
        #endregion

        #region drawing
        internal void DrawCurve(PointF[] points)
        {
            graphics.DrawCurve(pen, points);
        }

        internal void DrawEllipse(float x, float y, float width, float height)
        {
            graphics.DrawEllipse(pen, x, y, width, height);
        }

        internal void DrawLine(float x1, float y1, float x2, float y2)
        {
            graphics.DrawLine(pen, x1, y1, x2, y2);
        }

        internal void Clear()
        {
            graphics.Clear(Color.White);
            DrawAxis();
        }

        private void DrawAxis()
        {
            graphics.DrawLine(pen, 0, -ScaledHalfBoxHeight, 0, ScaledHalfBoxHeight);
            graphics.DrawLine(pen, -ScaledHalfBoxWidth, 0, ScaledHalfBoxWidth, 0);
        }
        #endregion

        #region scaling
        private void BtnScaleDownClick(object sender, EventArgs e)
        {
            if (scale >= MaxScale)
            {
                BtnScaleUp.Show();
            }

            ScaleCurves(1 / ScaleMultiplier);

            if (scale <= MinScale)
            {
                BtnScaleDown.Hide();
            }
        }

        private void BtnScaleUpClick(object sender, EventArgs e)
        {
            if (scale <= MinScale)
            {
                BtnScaleDown.Show();
            }

            ScaleCurves(ScaleMultiplier);

            if (scale >= MaxScale)
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

            model.Draw();
        }
        #endregion
    }
}
