using Libs;
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using Libs;
using Libs.Charts;
using System.Windows;
using System.Drawing;

namespace DrawChartWF
{

    public partial class Form1 : Form
    {
        #region Globals
        /// <summary>
        /// для работы с графиками и точками
        /// </summary>
        ChartHelper cHelper = new ChartHelper();
        /// <summary>
        /// текущий масштаб
        /// </summary>
        double _scaleCurr = 1;
        /// <summary>
        /// шаг масштабирования
        /// </summary>
        double scaleStep = 0.1;
        /// <summary>
        /// текущий масштаб
        /// </summary>
        public double scaleCurr
        {
            set
            {
                _scaleCurr = Math.Max(1, value);
            }
            get
            {
                return _scaleCurr;
            }
        }
        #endregion

        #region Lists
        List<System.Windows.Point> points = new List<System.Windows.Point>();
        List<float> values = new List<float>();
        List<Chart> charts = new List<Chart>();
        List<Line> lines = new List<Line>();
        #endregion

        #region Methods
        private void ClearImage()
        {
            pictureBox1.Image = new Bitmap(500, 500);
            using (Graphics g = Graphics.FromImage(pictureBox1.Image))
            {
                g.Clear(Color.White);
            }
        }
        private void DrawPoints(List<System.Windows.Point> points)
        {
            DrawPoints(points, 0, 0);
        }
        private void DrawPoints(List<System.Windows.Point> points, int dx, int dy)
        {
            using (Graphics g = Graphics.FromImage(pictureBox1.Image))
            {
                Pen pen = new Pen(Color.Black);
                for (int i = 0; i < points.Count - 1; i++)
                {
                    System.Windows.Point p = cHelper.MovePoint(cHelper.InverseY(points[i]), dx, dy);
                    System.Windows.Point p1 = cHelper.MovePoint(cHelper.InverseY(points[i + 1]), dx, dy);
                    if (!Double.IsNaN(p.X) && !Double.IsNaN(p.Y) && !Double.IsNaN(p1.X) && !Double.IsNaN(p1.Y))
                        g.DrawLine(pen, (float)p.X, (float)p.Y, (float)p1.X, (float)p1.Y);
                }
            }
        }
        private void DrawPoints(List<Line> lines, int dx, int dy)
        {
            foreach (Line line in lines)
                DrawPoints(line.GetPoints(), dx, dy);
        }
        private void UpdateImage()
        {
            int dx = Width / 2;
            int dy = Height / 2;
            ClearImage();
            UpdatePoints();
            if (points != null)
                DrawPoints(points, dx, dy);
            if (lines != null)
                DrawPoints(lines, dx, dy);
        }
        private void UpdatePoints()
        {
            points.Clear();
            lines.Clear();
            System.Windows.Point p = new System.Windows.Point(0, 0);
            System.Windows.Size size = new System.Windows.Size(Width, Height);
            lines.AddRange(cHelper.DrawAxis(p, size, scaleCurr, ChartHelper.Direction.horizontal));
            lines.AddRange(cHelper.DrawAxis(p, size, scaleCurr, ChartHelper.Direction.vertical));
            points = cHelper.GetPoints(charts, values, scaleCurr, comboBox1.SelectedIndex);
        }
        #endregion

        #region Constructors
        public Form1()
        {
            InitializeComponent();
            for (double i = -100; i < 100; i += 0.1)
                values.Add((float)i);
            charts.Add(new SqEqChart("Парабола", false));
            charts.Add(new CircleChart("Окружность", true));
            for (int i = 0; i < charts.Count; i++)
                comboBox1.Items.Add(charts[i].title);
            pictureBox1.MouseWheel += new MouseEventHandler(this.pictureBox1_MouseWheel);
        }
        #endregion

        #region Events
        private void Form1_Load(object sender, EventArgs e)
        {

        }
        private void pictureBox1_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Delta > 0)
                scaleCurr -= scaleStep;
            else
                scaleCurr += scaleStep;
            UpdateImage();
        }
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateImage();
        }
        #endregion
    }
}
