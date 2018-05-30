using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace Task_7
{
    public class WeakHashTable<TKey, TValue> where TValue : class
    {
        private int NumberOfBuckets { get; }

        public int TimeToStore { get; }

        public List<KeyValuePair<TKey, WeakReference<TValue>>>[] Buckets { get; }

        public WeakHashTable(int timeToStore, int numberOfBuckets = 10)
        {
            TimeToStore = timeToStore;
            NumberOfBuckets = numberOfBuckets;
            Buckets = new List<KeyValuePair<TKey, WeakReference<TValue>>>[NumberOfBuckets];

            for (int i = 0; i < NumberOfBuckets; ++i)
            {
                Buckets[i] = new List<KeyValuePair<TKey, WeakReference<TValue>>>();
            }
        }

        public async void Add(TKey key, TValue value)
        {
            int hash = Hash(key, NumberOfBuckets);
            WeakReference<TValue> reference = new WeakReference<TValue>(value);
            Buckets[hash]
                .Add(new KeyValuePair<TKey, WeakReference<TValue>>(key,reference));

            await Task.Delay(TimeToStore);
            reference.SetTarget(null);
        }

        public void Remove(TKey key)
        {
            int hash = Hash(key, NumberOfBuckets);

            foreach (var pair in Buckets[hash])
            {
                if (key.Equals(pair.Key))
                {
                    Buckets[hash].Remove(pair);
                    return;
                }
            }
        }

        public bool Contains(TKey key)
        {
            int hash = Hash(key, NumberOfBuckets);

            foreach (var pair in Buckets[hash])
            {
                if (key.Equals(pair.Key))
                {
                    return pair.Value.TryGetTarget(out var result);
                }
            }

            return false;
        }

        public TValue GetValue(TKey key)
        {
            int hash = Hash(key, NumberOfBuckets);
            TValue result = null;
            foreach (var pair in Buckets[hash])
            {
                if (key.Equals(pair.Key))
                {
                    pair.Value.TryGetTarget(out result);
                }
            }

            return result;
        }

        public int Hash(TKey key, int number) => Math.Abs(key.GetHashCode()) % number;
    }
}
