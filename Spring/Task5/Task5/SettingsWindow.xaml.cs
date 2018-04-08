using System.Net;
using System.Net.Sockets;
using System.Windows;

namespace Task5
{
    /// <summary>
    /// Interaction logic for SettingsWindow.xaml
    /// Singleton
    /// </summary>
    public sealed partial class SettingsWindow : Window
    {
        static SettingsWindow instance;

        // Omg I'm loving this syntax
        public static SettingsWindow Instance => instance ?? (instance = new SettingsWindow());

        // omg omg
        public static bool HasInstance => instance != null;

        SettingsWindow()
        {
            InitializeComponent();

            InitializeInformation();
            
            ConnectButton.Click += (sender, args) => ConnectWindow.Instance.Show();

            DisconnectButton.Click += OnDisconnectClicked;

            DoneButton.Click += (sender, args) => Close();

            Closing += (sender, cancelEventArgs) => instance = null;
        }

        void InitializeInformation()
        {
            InitializeIpAddress();

            var client = MainWindow.Instance.Client;
            
            IncomingConnectionsScreen.Text = $"Incoming connections: {client.IncomingConnectionsCount}";

            OutcomingConnectionsScreen.Text = $"Outcoming connection: {client.OutcomingConnectionIp ?? "none"}";

            DisconnectButton.IsEnabled = client.HasOutcomingConnection;

            ConnectButton.IsEnabled = !client.HasOutcomingConnection;
        }
        
        void InitializeIpAddress()
        {
            var addresses = Dns.GetHostAddresses(Dns.GetHostName());
            if (addresses.Length == 0)
            {
                MessageBox.Show("Could not access IP address", "Error");
                MainWindow.Instance.Close();
            }

            IpAddressScreen.Text = $"{addresses.Length}\r\n";

            foreach (var address in addresses)
            {
                // ReSharper disable once InvertIf
                if (address.AddressFamily == AddressFamily.InterNetwork)
                {
                    IpAddressScreen.Text = $"IP address: {address}";
                    return;
                }
            }

            MessageBox.Show("Could not access IP address", "Error");
            MainWindow.Instance.Close();
        }


        #region callbacks

        void OnDisconnectClicked(object sender, RoutedEventArgs args)
        {
            MainWindow.Instance.Client.Disconnect();
            ConnectButton.IsEnabled = true;
            DisconnectButton.IsEnabled = false;
            OutcomingConnectionsScreen.Text = "Outcoming connection: none";
            
            var main = MainWindow.Instance;
            main.SendButton.IsEnabled = false;
        }

        #endregion
    }
}
