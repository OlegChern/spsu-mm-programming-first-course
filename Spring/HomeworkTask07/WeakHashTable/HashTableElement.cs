using System;

namespace WeakHashTable
{
    internal class HashTableElement<T> where T : class
	{
        #region fields
        private string key;
        private WeakReference<T> valueRef;
        private HashTableElement<T> next;
        #endregion

        #region properties
        internal string Key
		{
			get
            {
                return key;
            }
		}

        internal HashTableElement<T> Next
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
        #endregion

        internal HashTableElement(string key, T value)
		{
			this.key = key;
            this.valueRef = new WeakReference<T>(value);
            next = null;
		}

        internal bool TryGetValue(out T value)
        {
            return valueRef.TryGetTarget(out value);
        }

        /*private void Store(int storageTime)
        {
            HashTableElement<T> reference = this;
            Thread.Sleep(storageTime);
        }*/
    }
}
