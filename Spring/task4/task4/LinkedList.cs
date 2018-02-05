using System;
using System.Collections;
using System.Collections.Generic;

namespace task4
{
    class LinkedList<T> : ILinkedList<T>
    {
        private ListElement<T> first;
        private ListElement<T> last;
        private uint length;

        public uint Length { get => length; }

        public LinkedList()
        {
            first = null;
            last = null;
            length = 0;
        }

        public void AddToStart(T value)
        {
            throw new NotImplementedException();
        }

        public void AddToEnd(T value)
        {
            throw new NotImplementedException();
        }

        public bool Remove(T value)
        {
            throw new NotImplementedException();
        }

        public ListElement<T> PopFirst()
        {
            throw new NotImplementedException();
        }

        public ListElement<T> PopLast()
        {
            throw new NotImplementedException();
        }

        public bool Contains(T value)
        {
            throw new NotImplementedException();
        }

        public IEnumerator<T> GetEnumerator()
        {
            var element = first;
            while (element != null)
            {
                yield return element.Value;
                element = element.Next;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
