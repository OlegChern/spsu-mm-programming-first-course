using System;

namespace task4.HashTable
{
    public class HashTable<T>
    {
        private int numberOfLists;

        private List<T>[] lists;

        public HashTable(int numberOfLists)
        {
            this.numberOfLists = numberOfLists;
            this.lists = new List<T>[numberOfLists];
            for (int i = 0; i < numberOfLists; i++)
            {
                this.lists[i] = new List<T>();
            }
        }

        private int HashFunction(int key) => (Math.Abs(key) % numberOfLists);

        public void AddElement(T value, int key)
        {
            lists[HashFunction(key)].AddFirst(value, key);
        }

        public void DeleteElement(int key)
        {
            lists[HashFunction(key)].DeleteElement(key);
        }

        public T GetValueByKey(int key) => (lists[HashFunction(key)].GetValueByKey(key));

        public bool Contains(int key) => (lists[HashFunction(key)].Contains(key));

        public void PrintTable()
        {
            for (int i = 0; i < numberOfLists; i++)
            {
                lists[i].PrintList();
            }
        }

        public void DeleteTable()
        {
            for (int i = 0; i < numberOfLists; i++)
            {
                lists[i].DeleteList();
            }
            lists = null;
        }
    }
}
