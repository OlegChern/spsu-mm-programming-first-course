using System;
using System.Collections.Generic;

namespace HashTable
{
	public class HashTable<T>
	{
		#region constants
		private const float IncreaseMultiplier = 1.5f;

        private const int DefaultChainSize = 16;
        private const int MinAdmittedChainSize = 8;
        private const int MaxAdmittedChainSize = 2048;

        private const int DefaultTableSize = 64;
		private const int MinAdmittedTableSize = 4;
		private const int MaxAdmittedTableSize = 32768;
		#endregion

		#region variables
		private HashTableChain<T>[] chains;
		private int tableSize;
        private int maxChainSize;
        #endregion

        #region constructors
        /// <summary>
        /// Creates HashTable
        /// </summary>
        /// <param name="tableSize">amount of chains in table</param>
        /// <param name="maxChainSize">max amount of elements in chain</param>
        public HashTable(int tableSize, int maxChainSize)
		{
			if (tableSize < MinAdmittedTableSize)
			{
				this.tableSize = MinAdmittedTableSize;
			}
			else if (tableSize > MaxAdmittedTableSize)
			{
                this.tableSize = MaxAdmittedTableSize;
			}
			else
			{
                this.tableSize = tableSize;
			}

			chains = new HashTableChain<T>[tableSize];

			for (int i = 0; i < tableSize; i++)
			{
				chains[i] = new HashTableChain<T>();
			}

            this.maxChainSize = maxChainSize;
        }

        /// <summary>
        /// Creates HashTable with default max chain size
        /// </summary>
        /// <param name="tableSize">amount of chains in table</param>
        public HashTable(int tableSize) : this(tableSize, DefaultChainSize) { }

        /// <summary>
        /// Creates HashTable with default table size and max chain size
        /// </summary>
        public HashTable() : this(DefaultTableSize, DefaultChainSize) { }
        #endregion

        #region public methods
        /// <summary>
        /// Adds element to HashTable
        /// </summary>
        /// <param name="key">element's key</param>
        /// <param name="value">element's value</param>
        public void Add(string key, T value)
		{
			HashTableElement<T> newElement = new HashTableElement<T>(key, value);
			HashTableChain<T> chain = chains[Hash(key)];

			chain.Add(newElement);
			if (chain.ChainSize >= maxChainSize)
			{
				Rebalance();
			}
		}

		/// <summary>
		/// Removes element with given key
		/// </summary>
		/// <param name="key">key of element</param>
		public void Remove(string key)
		{
			HashTableChain<T> chain = chains[Hash(key)];
			chain.Remove(key);
		}

		/// <summary>
		/// Finds value with given key
		/// </summary>
		/// <param name="key">key to find</param>
		/// <param name="value">found value</param>
		public bool Find(string key, out T value)
		{
			HashTableElement<T> element = chains[Hash(key)].Find(key);
			if (element != null)
			{
				value = element.Value;
				return true;
			}

			value = default(T);
			return false;
		}

		public void Print()
		{
			Console.WriteLine("\nHash table:\n[hash key] [key]      [value]");

			for (int i = 0; i < tableSize; i++)
			{
				HashTableChain<T> chain = chains[i];
				int chainSize = chain.ChainSize;

				if (chainSize > 0)
				{
					Console.WriteLine();

					for (int j = 0; j < chainSize; j++)
					{
						HashTableElement<T> element = chain[j];

						Console.Write("{0, 10} {1, 10} {2, 12}\n", Hash(element.Key), element.Key, element.Value);
					}
				}
			}

			Console.WriteLine();
		}
		#endregion

		#region supporting methods
		private int Hash(string key)
		{
			int hash = 0;

			foreach (char c in key)
			{
				hash += c;
			}

			return hash % tableSize;
		}

		private void Rebalance()
		{
			int prevCount = tableSize;
			tableSize = (int)(prevCount * IncreaseMultiplier);

			HashTableChain<T>[] temp = new HashTableChain<T>[tableSize];
			for (int i = 0; i < tableSize; i++)
			{
				temp[i] = new HashTableChain<T>();
			}

			for (int i = 0; i < prevCount; i++)
			{
				HashTableChain<T> sourceChain = chains[i];

				// for each element in source chain recalculate hash key
				// chain[j] is an element of chain with index j
				for (int j = 0; j < sourceChain.ChainSize; j++)
				{
					// recalculate hash with new table size
					int hash = Hash(sourceChain[j].Key);

                    // create new element without pointer to the next one
                    HashTableElement<T> elem = new HashTableElement<T>(sourceChain[j].Key, sourceChain[j].Value);

                    // add element to new chain with recalculated hash key
                    temp[hash].Add(elem);
				}
			}

			chains = temp;
		}
		#endregion
	}
}
