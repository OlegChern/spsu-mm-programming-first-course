using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace Task7.WeakReference
{
    public class HashTable<T>
        where T: class
    {
        private class TableElement
        {
            public readonly int key;

            private WeakReference<T> value;

            public TableElement(int key, T value)
            {
                this.key = key;
                this.value = new WeakReference<T>(value);
            }

            public void ChangeValue(T newValue)
            {
                this.value.SetTarget(newValue);
            }

            public bool Exist()
            {
                return value.TryGetTarget(out T temp);
            }

            public T GetValue()
            {
                value.TryGetTarget(out T temp);
                return temp;
            }
        }

        private int time;

        private int numberOfLists;

        private List<TableElement>[] lists;

        public HashTable(int numberOfLists, int time)
        {
            this.numberOfLists = numberOfLists;
            this.time = time;
            this.lists = new List<TableElement>[numberOfLists];
            for (int i = 0; i < numberOfLists; i++)
            {
                this.lists[i] = new List<TableElement>();
            }
        }

        private int HashFunction(int key) => (Math.Abs(key) % numberOfLists);

        private bool ListIsEmpty(int number)
        {
            foreach(var temp in lists[number])
            {
                if(temp.Exist())
                {
                    return false;
                }
            }
            return true;
        }

        private bool ChangeValue(int key, T value)
        {
            int hashFunction = HashFunction(key);

            foreach (var temp in lists[hashFunction])
            {
                if (temp.key == key)
                {
                    temp.ChangeValue(value);
                    return true;
                }
            }

            return false;
        }

        private void AddNewValue(int key, T value)
        {
            int hashFunction = HashFunction(key);
            lists[hashFunction].Add(new TableElement(key, value));
        }

        public async void AddElement(int key, T value)
        {
            if (!ChangeValue(key, value))
            {
                AddNewValue(key, value);
            }

            await Task.Delay(time);
        }

        public void DeleteElement(int key)
        {
            int hashFunction = HashFunction(key);

            foreach (var temp in lists[hashFunction])
            {
                if (temp.key == key)
                {
                    lists[hashFunction].Remove(temp);
                    return;
                }
            }
        }

        public bool Contains(int key)
        {
            int hashFunction = HashFunction(key);

            foreach (var temp in lists[hashFunction])
            {
                if ((temp.key == key) && (temp.Exist()))
                {
                    return true;
                }
            }
            return false;
        }

        public T GetValueByKey(int key)
        {
            int hashFunction = HashFunction(key);

            foreach (var temp in lists[hashFunction])
            {
                if ((temp.key == key) && (temp.Exist()))
                {
                    return temp.GetValue();
                }
            }

            return default(T);
        }

        public void Print()
        {
            for(int i = 0; i < numberOfLists; i++)
            {
                Console.Write("{0}:  ", i);
                foreach (TableElement temp in lists[i])
                {
                    Console.Write("{0} - {1}, ", temp.key, temp.GetValue());
                }
                Console.Write('\b');
                Console.Write('\b');
                Console.Write(" \n");
            }
            Console.WriteLine();
        }
    }
}
