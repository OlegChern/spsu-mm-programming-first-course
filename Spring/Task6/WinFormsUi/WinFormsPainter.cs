using Math;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormsUi
{
    sealed class WinFormsPainter : Painter, IDisposable
    {
        Graphics graphics;

        Pen pen;

        protected override double ScreenWidth => MainForm.WindowWidth;

        protected override double ScreenHeight => MainForm.WindowHeight;

        public WinFormsPainter(Graphics graphics)
        {
            this.graphics = graphics;
            pen = new Pen(Color.Black, 2);
        }

        protected override void Clear()
        {
            graphics.Clear(Color.White);
        }

        protected override void PaintAxes()
        {
            var pen = new Pen(Color.Blue, 2);
            graphics.DrawLine(pen, ScreenWidth / 2, 0, ScreenWidth / 2, ScreenHeight);
            graphics.DrawLine(pen, 0, ScreenHeight / 2, ScreenWidth, ScreenHeight / 2);
            pen.Dispose();
        }

        protected override void PaintDot(Math.Point dot)
        {
            graphics.DrawEllipse(pen, (int) dot.Y, (int) dot.X, 2, 2);
        }

        public void Dispose()
        {
            pen?.Dispose();
        }
    }
}
