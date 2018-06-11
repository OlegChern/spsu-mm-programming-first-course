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
using System.Windows.Shapes;

namespace Chat
{
    /// <summary>
    /// Логика взаимодействия для Port.xaml
    /// </summary>
    public partial class Port : Window
    {
        public string MyName { get; set; }

        public Port()
        {
            InitializeComponent();
            Ok.IsEnabled = false;
            ServerPort.TextChanged += (sender, args) => Ok.IsEnabled = (ServerPort.Text.Length == 0) ? false : true;
        }

        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            if (UInt16.TryParse(ServerPort.Text, out var port))
            {
                var chat = new ChatWindow(port, MyName);
                Close();
                chat.Show();
            }
            else
            {
                ((ChatWindow)Owner).PrintException("Некорректный порт");
            }
        }

        private void Port_GotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            ((TextBox)sender).Text = null;
        }
    }
}
