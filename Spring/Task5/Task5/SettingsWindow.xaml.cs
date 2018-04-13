using System.ComponentModel;
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

            Closing += OnClose;

            StartListeningButton.Click += (sender, args) => StartListeningWindow.Instance.Show();

            StopListeningButton.Click += OnStopListeningClicked;
        }

        void InitializeInformation()
        {
            InitializeIpAddress();

            var client = MainWindow.Instance.Client;

            ListeningPortScreen.Text =
                $"Listening Port: {(client.ListeningPort >= 0 ? client.ListeningPort.ToString() : "None")}";

            IncomingConnectionsScreen.Text = $"Incoming connections: {client.IncomingConnectionsCount}";

            OutcomingConnectionsScreen.Text = $"Outcoming connection: {client.OutcomingConnectionIp ?? "None"}";

            DisconnectButton.IsEnabled = client.HasOutcomingConnection;

            ConnectButton.IsEnabled = !client.HasOutcomingConnection;

            StartListeningButton.IsEnabled = !client.IsListening;

            StopListeningButton.IsEnabled = client.IsListening;
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

        void OnClose(object sender, CancelEventArgs args)
        {
            instance = null;
            if (ConnectWindow.HasInstance)
            {
                ConnectWindow.Instance.Close();
            }
            if (StartListeningWindow.HasInstance)
            {
                StartListeningWindow.Instance.Close();
            }
        }

        void OnDisconnectClicked(object sender, RoutedEventArgs args)
        {
            MainWindow.Instance.Client.Disconnect();
            ConnectButton.IsEnabled = true;
            DisconnectButton.IsEnabled = false;
            OutcomingConnectionsScreen.Text = "Outcoming connection: none";
            
            var main = MainWindow.Instance;
            main.SendButton.IsEnabled = false;
        }

        void OnStopListeningClicked(object sender, RoutedEventArgs args)
        {
            MainWindow.Instance.Client.StopListening();
            StopListeningButton.IsEnabled = false;
            StartListeningButton.IsEnabled = true;
            ListeningPortScreen.Text = "Listening Port: None";
        }

        #endregion callbacks
    }
}
