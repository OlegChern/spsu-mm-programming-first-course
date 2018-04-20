using System;
using System.Collections.Generic;
using System.Drawing;

namespace Math
{
    public static class Extensions
    {
        public static void ForEach<T>(this IEnumerable<T> data, Action<T> action)
        {
            foreach (var t in data)
            {
                action(t);
            }
        } 

        public static void DrawLine(this Graphics graphics, Pen pen, double x1, double x2, double y1, double y2)
        {
            graphics.DrawLine(pen, (float)x1, (float)x2, (float)y1, (float)y2);
        }
    }
}
