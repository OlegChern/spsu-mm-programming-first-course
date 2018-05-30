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
using System.Net.Sockets;
using System.Windows.Threading;

namespace Chat
{
    /// <summary>
    /// Логика взаимодействия для Window1.xaml
    /// </summary>
    public partial class ChatWindow : Window
    {
        public User User { get; set; }

        public IPAddress IP { get; set; }

        public string MyName { get; set; }

        public ChatWindow()
        {
            InitializeComponent();
            Send.IsEnabled = false;
            Disconnect.IsEnabled = false;
            MessageText.TextChanged += (sender, args) => Send.IsEnabled = ((MessageText.Text.Length == 0) || (User == null )) ? false : true;
            var addresses = Dns.GetHostAddresses(Dns.GetHostName());
            foreach (var e in addresses)
            {
                if (e.AddressFamily == AddressFamily.InterNetwork)
                {
                    IP = e;
                }
            }
            Address.Text = "Адрес: " + IP + " : ";
        }

        public void PrintMessageAsync(string str)
        {
            Dispatcher.BeginInvoke(new Action<string>((z) => ChatText.Text += str), str);
        }

        public void PrintMessage(string str)
        {
            new Action<string>(PrintMessageAsync).BeginInvoke(str, null, null);
        }

        public void PrintException(string ex)
        {
            MessageBox.Show(ex);
        }

        private void Send_Click(object sender, RoutedEventArgs e)
        {
            var str = $"{MyName}: " + MessageText.Text + "\n";
            User.Send(str);
            MessageText.Text = null;
        }

        private void Host_Click(object sender, RoutedEventArgs e)
        {
            var enterPort = new Port()
            {
                Owner = this
            };
            enterPort.Show();
        }

        private void Connect_Click(object sender, RoutedEventArgs e)
        {
            var enterIP = new IP()
            {
                Owner = this
            };
            enterIP.Show();
        }

        public void Disconnect_Click(object sender, RoutedEventArgs e)
        {
            DisconnectChat();
        }

        public void DisconnectAsync()
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                User.Disconnect();
                User = null;
                Host.IsEnabled = true;
                Connect.IsEnabled = true;
                Disconnect.IsEnabled = false;
                Address.Text = "Адрес: " + IP + " : ";
                ChatText.Text = null;
            }));
        }

        public void DisconnectChat()
        {
            new Action(DisconnectAsync).BeginInvoke(null, null);
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            if (User != null)            
            {
                DisconnectChat();
            }
            Close();
        }
    }
}
