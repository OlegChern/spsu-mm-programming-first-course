using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MathInfo;

namespace WindowsForms
{
    public partial class MyForm : Form
    {
        private double scalePaint;

        public double ScalePaint
        {
            get
            {
                return scalePaint;
            }
            set
            {
                if (value > 1)
                {
                    scalePaint = 1;
                }
                else if (value < 0.1)
                {
                    scalePaint = 0.1;
                }
                else
                {
                    scalePaint = value;
                }
            }
        }

        public Curve Curve { get; private set; }

        public Size StartSize { get; private set; }

        readonly Pen penSystem;

        readonly Pen penGraph;

        public Graphics Graphic { get; private set; }

        public Point[] PositivePoints { get; private set; }

        public Point[] NegativePoints { get; private set; }

        public MyForm()
        {
            InitializeComponent();
            penSystem = new Pen(Brushes.Black, 0.5f);
            penGraph = new Pen(Brushes.SlateBlue, 3f);
            ScalePaint = 0.5;

            var box = new ComboBox()
            {
                Dock = DockStyle.Fill
            };
            box.Items.AddRange(new Curve[] { new Ellips(), new Hyperbola(), new Parabola()});
            box.MouseWheel += (sender, args) =>
            {
                ((HandledMouseEventArgs)args).Handled = true;
                ScalePaint += (args.Delta > 0) ? 0.05 : -0.05;
                if ((PositivePoints != null) && (NegativePoints != null))
                {
                    ChangeGraphic((ComboBox)sender);
                }
            };
            SizeChanged += (sender, args) =>
            {
                if ((PositivePoints != null) && (NegativePoints != null))
                {
                    ChangeGraphic(box);
                }
            };
            box.SelectedIndexChanged += (sender, args) => ChangeGraphic((ComboBox)sender);

            Controls.Add(box);           
        }

        protected void ChangeGraphic(ComboBox box)
        {
            box.Focus();
            var region = new MathInfo.Region(new Point(0, 0), new Point(ClientSize.Width, ClientSize.Height));
            Curve = (Curve)box.SelectedItem;
            Curve.BuildCurve(region, ScalePaint);
            PositivePoints = Curve.PositivePoints.ToArray();
            NegativePoints = Curve.NegativePoints.ToArray();
            PaintGraphic();        
        }

        public void PaintGraphic()
        {
            Graphic.Clear(Color.FloralWhite);
            Graphic = CreateGraphics();
            Graphic.TranslateTransform(ClientSize.Width / 2, ClientSize.Height / 2);
            PaintSystem();
            if ((PositivePoints.Count() != 0) && (NegativePoints.Count() != 0))
            {
                if (Curve is Ellips)
                {
                    Graphic.DrawClosedCurve(penGraph, PositivePoints.Concat(NegativePoints).ToArray());
                }
                else
                {
                    Graphic.DrawCurve(penGraph, PositivePoints);
                    Graphic.DrawCurve(penGraph, NegativePoints);
                }
            }
            Graphic.TranslateTransform(-ClientSize.Width / 2, -ClientSize.Height / 2);
        }

        public void PaintSystem()
        {
            Graphic.DrawLine(penSystem, -ClientSize.Width / 2, 0, ClientSize.Width / 2, 0);
            Graphic.DrawLine(penSystem, 0, -ClientSize.Height / 2, 0, ClientSize.Height / 2);
            int step = (int)(StartSize.Width / 10 * ScalePaint);
            for (int i = 0; i < ClientSize.Width / 2; i += step)
            {
                Graphic.DrawLine(penSystem, i, -5, i, 5);
                Graphic.DrawLine(penSystem, -i, -5, -i, 5);
            }
            for (int i = 0; i < ClientSize.Height / 2; i += step)
            {
                Graphic.DrawLine(penSystem, -5, i, 5, i);
                Graphic.DrawLine(penSystem, -5, -i, 5, -i);
            }
        }

        private void MyForm_Load(object sender, EventArgs e)
        {
            Graphic = CreateGraphics();
            StartSize = ClientSize;
        }
    }
}
