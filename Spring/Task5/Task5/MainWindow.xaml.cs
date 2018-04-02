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
using System.Windows.Navigation;
using System.Windows.Shapes;

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

        public static MainWindow Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new MainWindow();
                }
                return instance;
            }
        }

        IClient client;

        MainWindow()
        {
            InitializeComponent();

            // TODO: replace with actual client
            client = new FakeClient();

            try
            {
                client.StartListening();
            }
            catch (Exception)
            {
                MessageBox.Show($"Cannot access port {Client.ListeningPort}", "Error");
            }

            ExitApplicationButton.Click += OnExitClicked;

            SettingsButton.Click += OnSettingsClicked;

            SendButton.Click += OnSendClicked;
        }

        #region callbacks

        void OnExitClicked(object sender, RoutedEventArgs args)
        {
            if (client.IsListening)
            {
                client.StopListening();
            }
            if (client.IncomingConnectionsCount != 0)
            {
                client.TerminateIncomingConnections();
            }
            if (client.HasOutcomingConnection)
            {
                client.Disconnect();
            }
            Close();
        }

        void OnSettingsClicked(object sender, RoutedEventArgs args)
        {
            // TODO: verify this singleton works correctly
            SettingsWindow.Instance.Show();
        }

        void OnSendClicked(object sender, RoutedEventArgs args)
        {
            
        }

        #endregion callbacks

        void Send()
        {

        }
    }
}
