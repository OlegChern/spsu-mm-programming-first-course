using System;
using System.Collections;
using System.Collections.Generic;

namespace task4
{
    class LinkedList<T> : IEnumerable<T>
    {
        private ListElement<T> first;
        private ListElement<T> last;

        public ListElement<T> First { get => first; }

        public ListElement<T> Last { get => last; }

        public LinkedList(ListElement<T> first = null, ListElement<T> last = null)
        {
            this.first = first;
            this.last = last;
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
