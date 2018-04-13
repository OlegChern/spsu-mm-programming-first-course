// В какой-то момент я осознал,
// что эта программа не слишком хороша.
// Все классы в ней очень тесно переплетены,
// удобные механизмы событий,
// которые здесь были бы очень к месту,
// не используются, да и протестировать
// можно только всё сразу, да и то руками...

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
        const int TimerInterval = 60;

        static MainWindow instance;

        static string ipAddress;

        Timer Timer { get; }

        public static MainWindow Instance => instance ?? (instance = new MainWindow());

        internal IClient Client { get; }

        static string IpAddress => ipAddress ?? (ipAddress = Dns.GetHostAddresses(Dns.GetHostName())[0].ToString());

        MainWindow()
        {
            InitializeComponent();

            Client = new Client();

            ExitApplicationButton.Click += (sender, args) => Close();

            Closing += OnClose;

            InputBox.TextChanged += (sender, args) =>
                SendButton.IsEnabled = Client.HasConnections && !string.IsNullOrEmpty(InputBox.Text);

            SettingsButton.Click += (sender, args) => SettingsWindow.Instance.Show();

            SendButton.Click += OnSendButtonOnClick;

            Timer = new Timer(obj => Dispatcher.Invoke(Invalidate), null, TimerInterval, TimerInterval);
        }

        #region callbacks

        void OnSendButtonOnClick(object sender, RoutedEventArgs args)
        {
            string message = $"[{Title}] {InputBox.Text}";
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
            Timer.Dispose();

            if (Client.IsListening)
            {
                Client.StopListening();
            }

            if (Client.IncomingConnectionsCount != 0)
            {
                Client.TerminateIncomingConnections();
            }

            if (Client.HasOutcomingConnection)
            {
                Client.Disconnect();
            }

            if (SettingsWindow.HasInstance)
            {
                SettingsWindow.Instance.Close();
            }

            if (ConnectWindow.HasInstance)
            {
                ConnectWindow.Instance.Close();
            }

            if (StartListeningWindow.HasInstance)
            {
                StartListeningWindow.Instance.Close();
            }

            instance = null;
        }

        async void Invalidate()
        {
            var messagesData = await Client.Receive();

            foreach (var data in messagesData)
            {
                if (string.IsNullOrWhiteSpace(data.Message))
                {
                    continue;
                }

                if (Client.HasOutcomingConnection && data.Message == IpAddress)
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
                ChatScreen.Text += data.Message;

                await Client.Send(data);
            }
        }

        #endregion callbacks
    }
}
