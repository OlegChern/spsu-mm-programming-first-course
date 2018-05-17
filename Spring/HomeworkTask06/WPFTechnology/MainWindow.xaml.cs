using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Drawing;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WPFTechnology
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            // when all loaded, start initializing model
            Loaded += delegate
            {
                Model model = new Model();
                model.Canvas = DrawingCanvas;

                model.EnableScaleUpBtn += (bool x) => ScaleUpBtn.IsEnabled = x;
                model.EnableScaleDownBtn += (bool x) => ScaleDownBtn.IsEnabled = x;
                model.DrawGeometry += BindData;

                ScaleUpBtn.Click += new RoutedEventHandler(model.ScaleUp);
                ScaleDownBtn.Click += new RoutedEventHandler(model.ScaleDown);

                CurvesComboBox.SelectionChanged += delegate
                {
                    model.SelectCurve(CurvesComboBox.SelectedItem);
                };
            };
        }

        void BindData(Geometry geometry)
        {
            DrawingPath.Data = geometry;
        }
    }
}
