using System;
using System.Collections.Generic;
using System.ComponentModel;
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

namespace Task5
{
    /// <summary>
    /// Interaction logic for StartListeningWindow.xaml
    /// Singleton -- well, a kind of
    /// </summary>
    public sealed partial class StartListeningWindow : Window
    {
        static StartListeningWindow instance;

        public static StartListeningWindow Instance => instance ?? (instance = new StartListeningWindow());

        public static bool HasInstance => instance != null;

        StartListeningWindow()
        {
            InitializeComponent();

            PortInputBox.TextChanged += (obj, args) =>
                DoneButton.IsEnabled = int.TryParse(PortInputBox.Text, out int result) && result > 0;

            CancelButton.Click += (obj, args) => Close();

            DoneButton.Click += OnDoneClicked;

            Closing += (obj, args) => instance = null;
        }

        #region callbacks

        void OnDoneClicked(object sender, RoutedEventArgs args)
        {
            var client = MainWindow.Instance.Client;
            var settings = SettingsWindow.Instance;

            client.StartListening(int.Parse(PortInputBox.Text));
            
            if (client.IsListening)
            {
                settings.ListeningPortScreen.Text = $"Listening Port: {client.ListeningPort}";
                settings.StartListeningButton.IsEnabled = false;
                settings.StopListeningButton.IsEnabled = true;
                Close();
            }
        }

        #endregion callbacks
    }
}
