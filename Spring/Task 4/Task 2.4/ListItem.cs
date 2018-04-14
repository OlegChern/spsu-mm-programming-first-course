using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2._4
{
    class ListItem<T>
    {
        public T Value { get; set; }
        public ListItem<T> Next { get; set; }
        public ListItem<T> Prev { get; set; }
        public ListItem(T value, ListItem<T> next, ListItem<T> prev)
        {
            Value = value;
            Next = next;
            Prev = prev;
        }
    }
}
