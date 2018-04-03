using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_4
{
    internal class HashTable<T>
    {
        private readonly int _numberOfLists;

        private MyList<T>[] _lists;

        public HashTable(int numberOfLists)
        {
            _numberOfLists = numberOfLists;
            _lists = new MyList<T>[numberOfLists];
            for (int i = 0; i < numberOfLists; ++i)
            {
                _lists[i] = new MyList<T>();
            }
        }

        private int HashFunction(int key) => (Math.Abs(key) % _numberOfLists);

        public void AddElement(T value, int key)
        {
            _lists[HashFunction(key)].AddFirst(value, key);
        }

        public void DeleteElement(int key)
        {
            _lists[HashFunction(key)].DeleteElement(key);
        }

        public T GetValueByKey(int key) => (_lists[HashFunction(key)].GetValueByKey(key));

        public bool Contains(int key) => (_lists[HashFunction(key)].Contains(key));

        public void PrintTable()
        {
            for (int i = 0; i < _numberOfLists; ++i)
            {
                _lists[i].PrintList();
            }
        }

        public void DeleteTable()
        {
            for (int i = 0; i < _numberOfLists; ++i)
            {
                _lists[i].DeleteList();
            }

            _lists = null;
        }
    }

}

