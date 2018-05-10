using System;
using System.Windows.Forms;

namespace WinFormsTechnology
{
    internal class Controller
    {
        private Model model;

        public Controller(Model model)
        {
            this.model = model;
        }

        public void ComboBoxSelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox comboBox = (ComboBox)sender;
            model.Draw(comboBox.SelectedItem);
        }

        public void BtnScaleUpClick(object sender, EventArgs e)
        {
            model.ScaleUp();
        }

        public void BtnScaleDownClick(object sender, EventArgs e)
        {
            model.ScaleDown();
        }
    }
}
