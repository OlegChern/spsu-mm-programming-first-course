using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2._4
{
    class DoublyLinkedList<T> : IEnumerable<T>
        where T : IEquatable<T>
    {
        public ListItem<T> Head { get; set; }
        public ListItem<T> Tail { get; set; }
        public int Count { get; set; }

        public T this[int index]
        {
            get
            {
                if ((index < 0) || (index >= Count))
                {
                    throw new IndexOutOfRangeException();
                }
                int i = 0;
                foreach ( var e in this)
                {
                    if (i == index)
                    {
                        return e;
                    }
                    i++;
                }
                throw new IndexOutOfRangeException();
            }
            set
            {
                if ((index < 0) || (index >= Count))
                {
                    throw new IndexOutOfRangeException();
                }
                var item = Head;
                for (int i = 0; i < index; i++)
                {
                    item = item.Next;
                }
                item.Value = value;
            }
        }

        public void Print()
        {
            Console.Write("Вывод списка: ");
            if (Count == 0)
            {
                Console.WriteLine("Список пуст.");
                return;
            }
            foreach(var e in this)
            {
                Console.Write("{0} ", e);
            }
            Console.WriteLine();
            Console.WriteLine("Количество элементов: {0}", this.Count);
        }

        public void Add(T value)
        {
            if (Count == 0)
            {
                var item = new ListItem<T>(value, null, null);
                Head = Tail = item;
                Count++;
            }
            else
            {
                var item = new ListItem<T>(value, null, Tail);
                Tail.Next = item;
                Tail = item;
                Count++;
            }
        }

        public void AddFirst(T value)
        {
            if (Count == 0)
            {
                var item = new ListItem<T>(value, null, null);
                Head = Tail = item;
                Count++;
            }
            else
            {
                var item = new ListItem<T>(value, Head, null);
                Head.Prev = item;
                Head = item;
                Count++;
            }
        }

        public bool Contains(T value)
        {
            foreach (var e in this)
            {
                if (e.Equals(value))
                {
                    return true;
                }
            }
            return false;
        }

        public IEnumerator<T> GetEnumerator()
        {
            var item = Head;
            while (item != null)
            {
                yield return item.Value;
                item = item.Next;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Remove(T value)
        {
            if (!this.Contains(value))
            {
                throw new ArgumentException();
            }
            if (Head == Tail)
            {
                Head = Tail = null;
                Count--;
                return;
            }
            var item = Head;
            while (!(item.Value).Equals(value))
            {
                item = item.Next;
            }
            if (item.Prev == null)
            {
                (item.Next).Prev = null;
                Head = item.Next;
            }
            else
            {
                (item.Next).Prev = item.Prev;
                (item.Prev).Next = item.Next;
            }
            Count--;
        }

        public void Clear()
        {
            foreach(var e in this)
            {
                this.Remove(e);
            }
        }

    }
}
