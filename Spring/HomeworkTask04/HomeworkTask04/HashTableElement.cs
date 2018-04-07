using System;
using System.Collections.Generic;

namespace HashTable
{
	internal class HashTableElement<T>
	{
        #region fields
        private string key;
        private T value;
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

		internal T Value
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
            this.value = value;
            next = null;
		}
	}
}
