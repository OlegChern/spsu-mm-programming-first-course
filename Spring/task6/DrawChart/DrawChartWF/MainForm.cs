using Libs;
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using Libs.Charts;
using System.Drawing;
namespace DrawChartWF
{
    /// <summary>
    /// Главная форма
    /// </summary>
    public partial class MainForm : Form
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
            pbChart.Image = new Bitmap(this.Width, this.Height);
            using (Graphics g = Graphics.FromImage(pbChart.Image))
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
            using (Graphics g = Graphics.FromImage(pbChart.Image))
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
        private void UpdateInfoLabel()
        {
            lblInfo.Location = new Point(this.Width / 2 - lblInfo.Width / 2, this.Height - 60);
            lblInfo.Refresh();
        }
        private void UpdatePoints()
        {
            if (points != null)
                points.Clear();
            if (lines != null)
                lines.Clear();
            System.Windows.Point p = new System.Windows.Point(0, 0);
            System.Windows.Size size = new System.Windows.Size(Width, Height);
            lines.AddRange(cHelper.DrawAxis(p, size, scaleCurr, ChartHelper.Direction.horizontal));
            lines.AddRange(cHelper.DrawAxis(p, size, scaleCurr, ChartHelper.Direction.vertical));
            points = cHelper.GetPoints(charts, values, scaleCurr, cmbCharts.SelectedIndex);
        }
        #endregion

        #region Constructors
        public MainForm()
        {
            InitializeComponent();
            for (double i = -100; i < 100; i += 0.1)
                values.Add((float)i);
            charts.Add(new SqEqChart("Парабола", false));
            charts.Add(new CircleChart("Окружность", true));
            for (int i = 0; i < charts.Count; i++)
                cmbCharts.Items.Add(charts[i].title);
            pbChart.MouseWheel += new MouseEventHandler(this.PbChartMouseWheel);
        }
        #endregion

        #region Events
        private void MainFormLoad(object sender, EventArgs e)
        {
            cmbCharts.DropDownStyle = ComboBoxStyle.DropDownList;
        }
        private void PbChartMouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            if (e.Delta > 0)
                scaleCurr -= scaleStep;
            else
                scaleCurr += scaleStep;
            UpdateImage();
        }
        private void CbChartsSelectedIndexChanged(object sender, EventArgs e)
        {
            UpdateImage();
            pbChart.Focus();
        }
        private void MainFormSizeChanged(object sender, EventArgs e)
        {
            UpdateImage();
            UpdateInfoLabel();
        }
        #endregion
    }
}
