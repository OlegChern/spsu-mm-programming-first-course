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

namespace Task5
{
    /// <summary>
    /// Interaction logic for SettingsWindow.xaml
    /// Singleton
    /// </summary>
    public sealed partial class SettingsWindow : Window, IDisposable
    {
        static SettingsWindow instance;

        public static SettingsWindow Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new SettingsWindow();
                }
                return instance;
            }
        }

        bool isDisposed;

        SettingsWindow()
        {
            isDisposed = false;
            InitializeComponent();
        }

        public void Dispose()
        {
            isDisposed = true;
            instance = null;
        }

        #region callbacks

        // TODO: check that object is not disposed

        #endregion
    }
}
