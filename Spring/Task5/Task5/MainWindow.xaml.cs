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
        static MainWindow instance;

        public static MainWindow Instance => instance ?? (instance = new MainWindow());

        internal IClient Client { get; }

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

            Client.StartTimer();

            Client.MessageReceived += s => Dispatcher.Invoke(() => ChatScreen.Text += $"{Environment.NewLine}{s}");

            Client.AutoDisconnected += () =>
                Dispatcher.Invoke(() => MessageBox.Show("Disconnected due to loops in network", "Disconnectted"));
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
            Client.Dispose();

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

        #endregion callbacks
    }
}
