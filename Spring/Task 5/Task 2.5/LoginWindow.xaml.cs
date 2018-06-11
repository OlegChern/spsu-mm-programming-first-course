using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Chat
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
            Login.IsEnabled = false;
            NameClient.TextChanged += (sender, args) => Login.IsEnabled = (NameClient.Text.Length == 0) ? false : true;               
        }

        private void Login_Click(object sender, RoutedEventArgs e)
        {
            var port = new Port
            {
                MyName = NameClient.Text
            };
            port.Show();
            Close();
        }       

        private void Name_GotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            ((TextBox)sender).Text = null;
        }
    }
}
