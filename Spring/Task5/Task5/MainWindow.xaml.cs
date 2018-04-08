using System;
using System.ComponentModel;
using System.Net;
using System.Threading;
using System.Windows;

namespace Task5
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// Closely connected with IClient
    /// Singleton
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        public const int TimerInterval = 60;

        static MainWindow instance;

        static string ipAddress;

        Timer Timer { get; set; }

        public static MainWindow Instance => instance ?? (instance = new MainWindow());

        internal IClient Client { get; }

        static string IpAddress =>
            ipAddress ?? (ipAddress = Dns.GetHostAddresses(Dns.GetHostName())[0].ToString());

        MainWindow()
        {
            InitializeComponent();

            Client = new Client();

            try
            {
                // Ok, let's just hope it executes quicly enough
                Client.StartListening();
            }
            catch (Exception)
            {
                MessageBox.Show($"Cannot access port {Task5.Client.ListeningPort}", "Error");
                Close();
            }

            ExitApplicationButton.Click += (sender, args) => Close();

            Closing += OnClose;

            InputBox.TextChanged += (sender, args) =>
                SendButton.IsEnabled = Client.HasConnections && !string.IsNullOrEmpty(InputBox.Text);

            SettingsButton.Click += (sender, args) => SettingsWindow.Instance.Show();

            SendButton.Click += OnSendButtonOnClick;
            
            Timer = new Timer(Invalidate, null, TimerInterval, TimerInterval);
        }

        #region callbacks

        void OnSendButtonOnClick(object sender, RoutedEventArgs args)
        {
            string message = InputBox.Text;
            InputBox.Text = "";
            try
            {
                Client.Send(message);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Error");
                return;
            }

            ChatScreen.Text += Environment.NewLine;
            ChatScreen.Text += message;
        }

        void OnClose(object sender, CancelEventArgs args)
        {
            // Yeah, ignoring all exceptions here, shame on me
            try
            {
                Timer.Dispose();
            }
            catch (Exception)
            {
                // ignore
            }
            
            try
            {
                Client.StopListening();
            }
            catch (Exception)
            {
                // ignore
            }

            try
            {
                Client.TerminateIncomingConnections();
            }
            catch (Exception)
            {
                // ignore
            }

            try
            {
                Client.Disconnect();
            }
            catch (Exception)
            {
                // ignore
            }

            if (SettingsWindow.HasInstance)
            {
                SettingsWindow.Instance.Close();
            }

            if (ConnectWindow.HasInstance)
            {
                ConnectWindow.Instance.Close();
            }

            instance = null;
        }

        async void Invalidate(object arg)
        {
            var messageTasks = Client.Receive();
            foreach (var messageTask in messageTasks)
            {
                string message = await messageTask;
                if (string.IsNullOrWhiteSpace(message))
                {
                    continue;
                }

                if (Client.HasOutcomingConnection && message == IpAddress)
                {
                    Client.Disconnect();
                    ConnectiosScreen.Text = $"Connections: {Client.IncomingConnectionsCount}";
                    if (SettingsWindow.HasInstance)
                    {
                        SettingsWindow.Instance.OutcomingConnectionsScreen.Text =
                            $"OutcomingConnection: {Client.OutcomingConnectionIp}";
                        SettingsWindow.Instance.ConnectButton.IsEnabled = true;
                        SettingsWindow.Instance.DisconnectButton.IsEnabled = false;
                    }

                    if (!Client.HasConnections)
                    {
                        SendButton.IsEnabled = false;
                    }
                }

                ChatScreen.Text += Environment.NewLine;
                ChatScreen.Text += message;
            }
        }

        #endregion callbacks
    }
}
