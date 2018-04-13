﻿using System;
using System.Net;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Task5
{
    /// <summary>
    /// Interaction logic for ConnectWindow.xaml
    /// Singleton
    /// </summary>
    public partial class ConnectWindow : Window
    {
        static ConnectWindow instance;

        public static ConnectWindow Instance => instance ?? (instance = new ConnectWindow());

        public static bool HasInstance => instance != null;

        ConnectWindow()
        {
            InitializeComponent();

            IpInputBox.TextChanged += OnTextChanged;

            DoneButton.Click += OnDoneButtonOnClick;

            CancelButton.Click += (sender, args) => Close();

            Closing += (sender, args) => instance = null;
        }

        async void OnDoneButtonOnClick(object sender, RoutedEventArgs args)
        {
            DoneButton.IsEnabled = false;
            CancelButton.IsEnabled = false;
            IpInputBox.IsEnabled = false;
            PortInputBox.IsEnabled = false;
            try
            {
                int port =
                    string.IsNullOrEmpty(PortInputBox.Text)
                        ? Client.DefaultListeningPort
                        : int.Parse(PortInputBox.Text);
                await MainWindow.Instance.Client.Connect(IpInputBox.Text, port);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Error");
                DoneButton.IsEnabled = true;
                CancelButton.IsEnabled = true;
                IpInputBox.IsEnabled = true;
                PortInputBox.IsEnabled = true;
                return;
            }

            var settings = SettingsWindow.Instance;
            settings.ConnectButton.IsEnabled = false;
            settings.DisconnectButton.IsEnabled = true;
            settings.OutcomingConnectionsScreen.Text =
                $"Outcoming connection: {MainWindow.Instance.Client.OutcomingConnectionIp}";

            var main = MainWindow.Instance;
            main.SendButton.IsEnabled = !string.IsNullOrEmpty(main.InputBox.Text);
            main.ConnectiosScreen.Text = $"Connections: {main.Client.IncomingConnectionsCount + 1}";
            Close();
        }

        #region callbacks

        void OnTextChanged(object sender, TextChangedEventArgs args)
        {
            string text = IpInputBox.Text;
            bool isIp = !string.IsNullOrWhiteSpace(text) && text.Split('.').Length == 4 &&
                        IPAddress.TryParse(text, out var _);
            DoneButton.IsEnabled = isIp;
        }

        #endregion callbacks
    }
}
