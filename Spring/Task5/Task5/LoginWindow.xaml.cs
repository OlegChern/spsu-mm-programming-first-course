using System;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace Task5
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public sealed partial class LoginWindow
    {
        public LoginWindow()
        {
            InitializeComponent();

            NameInputTextBox.TextChanged += (sender, args) =>
            {
                if (!string.IsNullOrEmpty(NameInputTextBox.Text))
                {
                    NameInputTextBox.Background = (SolidColorBrush)FindResource("BaseBackground");
                    LoginButton.IsEnabled = Regex.IsMatch(NameInputTextBox.Text, @"\A\S{3,}\z");
                }
                else
                {
                    NameInputTextBox.Background = null;
                    LoginButton.IsEnabled = false;
                }
            };

            ExitButton.Click += (sender, args) => Close();

            LoginButton.Click += (sender, args) =>
            {
                var mainWindow = MainWindow.Instance;
                mainWindow.Title = NameInputTextBox.Text;
                mainWindow.Show();
                Close();
            };
        }
    }
}
