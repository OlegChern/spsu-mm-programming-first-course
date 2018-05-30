using System;
using System.Collections.Generic;
using System.Linq.Expressions;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WeakHashtable
{
    public class WeakHashTable<T>
        where T : class
    {       
        public int TableSize { get; private set; }

        public int MaxSizeRow { get; }
      
        public int TimeStorage { get; }

        public  List<Element<T>>[] HashTable { get; private set; }

        public int Hash(string key)
        {
            int hash = Math.Abs(key.GetHashCode()) % TableSize;
            return hash;
        }

        public WeakHashTable(int size, int sizeRow, int timeStorage)
        {
            TableSize = size;
            MaxSizeRow = sizeRow;
            TimeStorage = timeStorage;
            HashTable = new List<Element<T>>[TableSize];
            for (int i = 0; i < TableSize; i++)
            {
                HashTable[i] = new List<Element<T>>();
            }
        }

        private void Rebalance()
        {
            TableSize *= 2;
            var newHashTable = new List<Element<T>>[TableSize];
            for (int i = 0; i < TableSize; i++)
            {
                newHashTable[i] = new List<Element<T>>();
            }
            HashTable.ToList().ForEach(z =>
            {
                z.ForEach(e =>
                {
                    e.RefValue.TryGetTarget(out var value);
                    if (value != null)
                    {
                        Add(newHashTable, e.Key, value);
                    }
                    value = null;
                });
            });
            HashTable = newHashTable;
        }
        
        private void Add(List<Element<T>>[] table, string key, T value)
        {
            foreach (var z in table[Hash(key)])
            {
                if (z.Key == key)
                {
                    z.RefValue.SetTarget(value);
                    return;
                }                            
            };
            table[Hash(key)].Add(new Element<T>(key, value));
        }

        public async void SetValue(string key, T value)
        {
            Add(HashTable, key, value);

            while (HashTable[Hash(key)].Count > MaxSizeRow)
            {
                ExpansionTable();
            }

            await Task.Delay(TimeStorage);
        }

        public bool Remove(string key)
        {
            Element<T> elem = null;
            foreach (var z in HashTable[Hash(key)])
            {
                if (z.Key == key)
                {
                    elem = z;
                    break;
                }
            };
            if (elem != null)
            {
                return HashTable[Hash(key)].Remove(elem);
            }
            return false;
        }

        public bool ContainsKey(string key)
        {
            bool result = false;
            foreach (var z in HashTable[Hash(key)])
            {
                if (z.Key == key)
                {
                    result = z.RefValue.TryGetTarget(out var target);
                    target = null;
                    break;
                }
            };
            return result;
        }

        public T TryGetValue(string key)
        {
            T value = null;
            foreach (var z in HashTable[Hash(key)])
            {
                if (z.Key == key)
                {
                    z.RefValue.TryGetTarget(out value);
                    break;
                }
            };
            return value;
        }

        public void Print()
        {
            Console.WriteLine("Хэш-таблица:");
            for (int i = 0; i < TableSize; i++)
            {
                Console.Write("[{0}]:", i);
                foreach(var e in HashTable[i])
                {
                    Console.Write(" -> (\"{0}\"", e.Key);
                    e.RefValue.TryGetTarget(out T value);
                    Console.Write(", {0})", value);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
    }
}
