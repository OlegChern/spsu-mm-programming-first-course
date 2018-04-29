using System;
using System.Windows.Forms;

namespace WinFormsTechnology
{
    public static class WinFormsProgram
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}
