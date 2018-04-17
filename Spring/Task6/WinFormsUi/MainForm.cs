using System.Drawing;
using System.Windows.Forms;

namespace WinFormsUi
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Paint(object sender, PaintEventArgs e)
        {
            Graphics graphicsObj;

            graphicsObj = CreateGraphics();
        }
    }
}
