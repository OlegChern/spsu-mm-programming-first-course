using System;

namespace Math
{
    public struct Region
    {
#if DEBUG
        public readonly Point UpperLeft;
        public readonly Point LoweRight;
#else
        Point upperLeft;
        Point lowerRight;
#endif

        public double Width => LoweRight.X - UpperLeft.Y;

        public double Height => LoweRight.Y - UpperLeft.Y;

        public Region(Point upperLeft, Point loweRight)
        {
            // TODO: verify that this assertation is correct
            if (upperLeft.X >= loweRight.X || upperLeft.Y >= loweRight.Y)
            {
                throw new ArgumentException(
                    "upper-left corner should actually be upper-left relatively to lower-right one");
            }

            UpperLeft = upperLeft;
            LoweRight = loweRight;
        }
    }
}
