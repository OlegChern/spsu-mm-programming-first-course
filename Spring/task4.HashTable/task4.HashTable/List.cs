using System;

namespace task4.HashTable
{
    public class List<T>
    {
        private class ListElement
        {
            private T value;

            public T Value
            {
                get
                {
                    return value;
                }
                private set
                {
                    this.value = value;
                }
            }

            private int key;

            public int Key
            {
                get
                {
                    return key;
                }
                private set
                {
                    key = value;
                }
            }

            private ListElement next;

            public ListElement Next
            {
                get
                {
                    return next;
                }
                set
                {
                    next = value;
                }
            }

            public ListElement(T value, int key, ListElement next)
            {
                this.Value = value;
                this.Key = key;
                this.Next = next;
            }
        }

        private int length;

        public int Length
        {
            get
            {
                return length;
            }
            private set
            {
                length = value;
            }
        }

        private ListElement first;

        public List()
        {
            this.first = null;
            this.Length = 0;
        }

        public void AddFirst(T value, int key)
        {
            var newElement = new ListElement(value, key, first);
            first = newElement;
            Length++;
        }

        public T GetValueByKey(int key)
        {
            ListElement temp = first;
            while(temp != null)
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
            while ((first != null) && (first.Key == key))
            {
                first = first.Next;
                Length--;
            }

            ListElement temp = first;
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
            ListElement temp = first;
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
            if(first == null)
            {
                return;
            }
            ListElement temp = first;
            while (temp != null)
            {
                Console.Write(temp.Value);
                Console.Write(" ");
                temp = temp.Next;
            }
            Console.WriteLine();
        }

        public void DeleteList()
        {
            first = null;
        }
    }
}
