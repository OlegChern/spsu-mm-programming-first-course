using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MathInfo
{
    public class Region
    {
        public Point UpLeft { get; set; }

        public Point DownRight { get; set; }

        public Region(Point upLeft, Point downRight)
        {
            UpLeft = upLeft;
            DownRight = downRight;
        }

        public int Width
        {
            get
            {
                return Math.Abs(UpLeft.X - DownRight.X);
            }
        }

        public int Height
        {
            get
            {
                return Math.Abs(UpLeft.Y - DownRight.Y);
            }
        }

    }
}
