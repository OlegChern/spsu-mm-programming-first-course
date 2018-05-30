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
using System.Net;

namespace Chat
{
    /// <summary>
    /// Логика взаимодействия для IP.xaml
    /// </summary>
    public partial class IP : Window
    {
        public IP()
        {
            InitializeComponent();
            Ok.IsEnabled = false;
            ServerIP.TextChanged += (sender, args) => Ok.IsEnabled = (ServerIP.Text.Length == 0) ? false : true;
        }

        private void Ok_Click(object sender, RoutedEventArgs e)
        {
            if ((IPAddress.TryParse(ServerIP.Text, out var ip)) && (UInt16.TryParse(ServerPort.Text, out var port)))
            {
                var chat = (ChatWindow)Owner;
                chat.User = new Client(chat.Name, port, ip, chat);
                if (chat.User.IsConnect)
                {
                    chat.Host.IsEnabled = false;
                    chat.Connect.IsEnabled = false;
                    chat.Disconnect.IsEnabled = true;
                    chat.Address.Text = "-----";
                }
                else
                {
                    chat.User = null;
                }
                Close();
            }
            else
            {
                ((ChatWindow)Owner).PrintException("Некорректный адресс");
            }
        }

        private void ServerIP_GotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            ((TextBox)sender).Text = null;
        }

        private void ServerPort_GotKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            ((TextBox)sender).Text = null;
        }
    }
}
