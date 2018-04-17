using System;
using System.Collections.Generic;

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
    }
}
