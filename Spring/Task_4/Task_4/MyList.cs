using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_4
{
    internal class MyList<T>
    {
        public int Length { get; private set; }

        private ListElement<T> _first;

        public MyList()
        {
            _first = null;
            Length = 0;
        }

        public void AddFirst(T value, int key)
        {
            var newElement = new ListElement<T>(value, key, _first);
            _first = newElement;
            Length++;
        }

        public T GetValueByKey(int key)
        {
            ListElement<T> temp = _first;
            while (temp != null)
            {
                if (temp.Key == key)
                {
                    return temp.Value;
                }

                temp = temp.Next;
            }

            return default(T);
        }

        public void DeleteElement(int key)
        {
            while ((_first != null) && (_first.Key == key))
            {
                _first = _first.Next;
                Length--;
            }

            ListElement<T> temp = _first;
            while (temp != null)
            {
                while ((temp.Next != null) && (temp.Next.Key == key))
                {
                    temp.Next = temp.Next.Next;
                    Length--;
                }

                temp = temp.Next;
            }
        }

        public bool Contains(int key)
        {
            ListElement<T> temp = _first;
            while (temp != null)
            {
                if (temp.Key == key)
                {
                    return true;
                }

                temp = temp.Next;
            }

            return false;
        }

        public void PrintList()
        {
            if (_first == null)
            {
                return;
            }

            ListElement<T> temp = _first;
            while (temp != null)
            {
                Console.Write("{0} ",temp.Value);
                temp = temp.Next;
            }

            Console.WriteLine();
        }

        public void DeleteList()
        {
            _first = null;
        }
    }
}

