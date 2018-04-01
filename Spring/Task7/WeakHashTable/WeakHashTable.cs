using System;
using System.Collections;
using System.Collections.Generic;

namespace WeakHashTable
{
    public sealed class WeakHashTable<T>
        where T : class
    {
        const int InitialBuckets = 64;

        int bucketsCount;
        
        IList<IList<WeakReference<T>>> Buckets { get; set; }

        int MillisecondsToKeep { get; }

        public WeakHashTable() : this(300)
        {
        }

        public WeakHashTable(int time)
        {
            bucketsCount = InitialBuckets;
            Buckets = new IList<WeakReference<T>>[InitialBuckets];
            MillisecondsToKeep = time;
        }

        /// <summary>
        /// Doubles length of Buckets
        /// </summary>
        void Extend()
        {
            var oldBuckets = Buckets;
            bucketsCount *= 2;
            Buckets = new IList<WeakReference<T>>[bucketsCount];
            //Buckets.Add();
        }
    }
}
