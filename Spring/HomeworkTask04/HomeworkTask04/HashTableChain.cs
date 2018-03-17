using System;
using System.Collections.Generic;

namespace HashTable
{
	internal class HashTableChain<T>
	{
		#region variables
		private HashTableElement<T>[] elements;
		internal int ChainSize
		{
			get;
			private set;
		}

		internal HashTableElement<T> this[int i]
		{
			get
			{
				if (i >= 0 && i < ChainSize)
				{
					return elements[i];
				}

				return null;
			}
		}
		#endregion

		#region constructor
		internal HashTableChain(int maxChainSize)
		{
			elements = new HashTableElement<T>[maxChainSize];
			ChainSize = 0;
		}
		#endregion

		#region methods
		internal void AddElement(HashTableElement<T> element)
		{
			elements[ChainSize] = element;
			ChainSize++;
		}

		internal HashTableElement<T> FindElement(string key)
		{
			for (int i = 0; i < ChainSize; i++)
			{
				HashTableElement<T> element = elements[i];
				if (element.Key == key)
				{
					return element;
				}
			}

			return null;
		}

		internal void ShiftElements(string key)
		{
			int index;

			if (FindElementIndex(key, out index))
			{
				// destroy element with index
				elements[index] = null;

				// shift elements are after index
				for (int i = index; i < ChainSize - 1; i++)
				{
					elements[i] = elements[i + 1];
				}

				// destroy last element
				elements[ChainSize] = null;

				ChainSize--;
			}
		}

		private bool FindElementIndex(string key, out int index)
		{
			for (int i = 0; i < ChainSize; i++)
			{
				if (elements[i].Key == key)
				{
					index = i;
					return true;
				}
			}

			index = -1;
			return false;
		}
		#endregion
	}
}
