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
        public ChatClient User { get; set; }

        public int Port { get; set; }

        public IPAddress IP { get; set; }

        public string MyName { get; set; }

        public ChatWindow(int port, string name)
        {
            InitializeComponent();
            Port = port;
            MyName = name;
            Send.IsEnabled = false;
            Disconnect.IsEnabled = false;
            MessageText.TextChanged += (sender, args) => Send.IsEnabled = (MessageText.Text.Length == 0) ? false : true;
            var addresses = Dns.GetHostAddresses(Dns.GetHostName());
            foreach (var e in addresses)
            {
                if (e.AddressFamily == AddressFamily.InterNetwork)
                {
                    IP = e;
                }
            }

            User = new ChatClient(MyName, Port, this);

            Address.Text = "Адрес: " + IP + " : " + Port;
            ChangeListAdress();
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
            User.Disconnect();
            Disconnect.IsEnabled = false;
            Connect.IsEnabled = true;
        }

        public void ChangeListAdressAsync()
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                ListAddress.Text = "Адреса пользователей:\n";
                foreach (var e in User.Points)
                {
                    ListAddress.Text += e.ToString() + "\n";
                }
            }));
        }

        public void ChangeListAdress()
        {
            new Action(ChangeListAdressAsync).BeginInvoke(null, null);
        }

        public void ConnectChatAsync()
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                Disconnect.IsEnabled = true;
            }));
        }

        public void ConnectChat()
        {
            new Action(ConnectChatAsync).BeginInvoke(null, null);
        }

        public void DisconnectChatAsync()
        {
            Dispatcher.BeginInvoke(new Action(() =>
            {
                Disconnect.IsEnabled = false;
                Connect.IsEnabled = true;
            }));
        }

        public void DisconnectChat()
        {
            new Action(DisconnectChatAsync).BeginInvoke(null, null);
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            User.Exit();
            Close();
        }
    }
}
