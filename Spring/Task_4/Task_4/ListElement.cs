using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_4
{
    internal class ListElement<T>
    {
        public T Value { get; }

        public int Key { get; }

        public ListElement<T> Next { get; set; }

        public ListElement(T value, int key, ListElement<T> next)
        {
            Value = value;
            Key = key;
            Next = next;
        }

    }
}
