using System;
using System.Collections.Generic;
using Math;

namespace WpfUi
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow
    {
        int pixelsInUnit;

        Painter painter;

        public MainWindow()
        {
            InitializeComponent();

            pixelsInUnit = 64;

            painter = new WpfPainter(Canvas);

            FunctionSelectionBox.ItemsSource = new List<CurveInfo>
            {
                new CircleInfo(2, 1, 2),
                new EllipticCurveInfo()
            };

            FunctionSelectionBox.SelectionChanged += (a, b) =>
                painter.Paint(b.AddedItems[0] as CurveInfo, pixelsInUnit);

            PlusButton.Click += (sender, args) =>
            {
                if (pixelsInUnit < 512)
                {
                    pixelsInUnit *= 2;
                    PlusButton.IsEnabled = true;
                    MinusButton.IsEnabled = true;
                }
                else
                {
                    pixelsInUnit = 1024;
                    PlusButton.IsEnabled = false;
                    MinusButton.IsEnabled = true;
                }

                painter.Paint(FunctionSelectionBox.SelectionBoxItem as CurveInfo, pixelsInUnit);
            };

            MinusButton.Click += (sender, args) =>
            {
                if (pixelsInUnit > 2)
                {
                    pixelsInUnit /= 2;
                    PlusButton.IsEnabled = true;
                    MinusButton.IsEnabled = true;
                }
                else
                {
                    pixelsInUnit = 1;
                    PlusButton.IsEnabled = true;
                    MinusButton.IsEnabled = false;
                }

                painter.Paint(FunctionSelectionBox.SelectionBoxItem as CurveInfo, pixelsInUnit);
            };

            SizeChanged += (sender, args) => painter.Paint(FunctionSelectionBox.SelectionBoxItem as CurveInfo, pixelsInUnit);
        }
    }
}
