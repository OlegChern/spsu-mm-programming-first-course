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
                var chat = (ChatWindow)Owner;
                chat.User = new Server(chat.Name, port, chat);
                if (chat.User.IsConnect)
                {
                    chat.Host.IsEnabled = false;
                    chat.Connect.IsEnabled = false;
                    chat.Disconnect.IsEnabled = true;
                    chat.Address.Text += port.ToString();
                }
                else
                {
                    chat.User = null;
                }
                Close();
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
