using System.Drawing;
using System.Windows.Forms;
using Math;

namespace WinFormsUi
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        void MainForm_Paint(object sender, PaintEventArgs e)
        {
            Controls.Add(new Button
            {
                Text = "+",
                DialogResult = DialogResult.Yes,
                Width = 80,
                Height = 24
            });
            Controls.Add(new Button
            {
                Left = 80,
                Width = 80,
                Height = 24,
                Text = "-",
                DialogResult = DialogResult.No
            });
            Controls.Add(new ComboBox
            {
                Left = 160,
                Width = 80,
                DisplayMember = "Name",
                Items = {new CircleInfo(2, 1, 2), new EllipticCurveInfo()}
            });

            Graphics g = CreateGraphics();
            g.Lef
        }

        void myPaint(CurveInfo curve)
        {
            
        }
        
        void PaintDot()
        {
            
        }
        
        void PaintAxes()
        {
        }
    }
}
