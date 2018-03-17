using System;
using System.Collections.Generic;

namespace HashTable
{
	internal class HashTableElement<T>
	{
		internal string Key
		{
			get;
			private set;
		}

		internal T Value
		{
			get;
			private set;
		}

		internal HashTableElement(string key, T value)
		{
			Key = key;
			Value = value;
		}
	}
}
