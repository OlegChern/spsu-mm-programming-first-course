using System;

namespace WeakHashTable
{
    internal class HashTableElement<T> where T : class
	{
        #region fields
        private string key;
        private WeakReference<T> value;
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

		internal WeakReference<T> Value
		{
			get
            {
                return value;
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
            this.value = new WeakReference<T>(value);
            next = null;
		}
	}
}
