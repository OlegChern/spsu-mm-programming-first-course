using System.Threading.Tasks;

namespace WeakHashTable
{
    public class WeakHashTable<T> where T : class
    {
        #region constants
        private const int DefaultStorageTime = 60000;
		private const float IncreaseMultiplier = 1.5f;

        private const int DefaultChainSize = 16;
        private const int MinAdmittedChainSize = 4;
        private const int MaxAdmittedChainSize = 2048;

        private const int DefaultTableSize = 64;
		private const int MinAdmittedTableSize = 4;
		private const int MaxAdmittedTableSize = 32768;
		#endregion

		#region variables
		private HashTableChain<T>[] chains;
		private int tableSize;
        private int maxChainSize;
        private int storageTime;
        #endregion

        #region properties
        public int StorageTime
        {
            get
            {
                return storageTime;
            }
        }
        #endregion

        #region constructors
        /// <summary>
        /// Creates WeakHashTable
        /// </summary>
        /// <param name="tableSize">amount of chains in table</param>
        /// <param name="maxChainSize">max amount of elements in chain</param>
        /// <param name="storageTime">elements' storage time in milliseconds</param>
        public WeakHashTable(int tableSize, int maxChainSize, int storageTime)
		{
            Normalize(ref tableSize, MinAdmittedTableSize, MaxAdmittedTableSize);
            Normalize(ref maxChainSize, MinAdmittedChainSize, MaxAdmittedChainSize);

			chains = new HashTableChain<T>[tableSize];

			for (int i = 0; i < tableSize; i++)
			{
				chains[i] = new HashTableChain<T>();
			}

            this.tableSize = tableSize;
            this.maxChainSize = maxChainSize;
            this.storageTime = storageTime < 0 ? 0 : storageTime;
        }

        #region additional contructors
        /// <summary>
        /// Creates WeakHashTable with default storage time
        /// </summary>
        /// <param name="tableSize">amount of chains in table</param>
        /// <param name="maxChainSize">max amount of elements in chain</param>
        public WeakHashTable(int tableSize, int maxChainSize) : this(tableSize, maxChainSize, DefaultStorageTime) { }

        /// <summary>
        /// Creates WeakHashTable with default max chain size and storage time
        /// </summary>
        /// <param name="tableSize">amount of chains in table</param>
        public WeakHashTable(int tableSize) : this(tableSize, DefaultChainSize, DefaultStorageTime) { }

        /// <summary>
        /// Creates WeakHashTable with default table size, max chain size and storage time
        /// </summary>
        public WeakHashTable() : this(DefaultTableSize, DefaultChainSize, DefaultStorageTime) { }
        #endregion
        #endregion

        #region public methods
        /// <summary>
        /// Adds element to WeakHashTable
        /// </summary>
        /// <param name="key">element's key</param>
        /// <param name="value">element's value</param>
        public void Add(string key, T value)
		{
            // first, asynchronously wait store time
            Wait(value);

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
				return element.TryGetValue(out value);
			}

			value = default(T);
			return false;
		}

        public override string ToString()
		{
            if (tableSize == 0)
            {
                return string.Empty;
            }

            string result = string.Empty;

            result += "\nHash table:\n[hash key] [key]      [value]";

			for (int i = 0; i < tableSize; i++)
			{
				HashTableChain<T> chain = chains[i];
				int chainSize = chain.ChainSize;

				if (chainSize > 0)
				{
                    result += '\n';

                    for (int j = 0; j < chainSize; j++)
					{
						HashTableElement<T> element = chain[j];

                        result += string.Format("{0, 10} {1, 10}", Hash(element.Key), element.Key);

                        T value;
                        if (element.TryGetValue(out value))
                        {
                            result += string.Format("{0, 12}", value);
                        }

                        result += '\n';
                    }
				}
			}

            return result;
		}
		#endregion

		#region supporting methods
        /// <summary>
        /// Calculates hash based on table size
        /// </summary>
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
                    T value;

                    // if we can get value-element then add it
                    if (sourceChain[j].TryGetValue(out value))
                    {
                        // recalculate hash with new table size
                        int hash = Hash(sourceChain[j].Key);

                        // create new element without pointer to the next one
                        HashTableElement<T> elem = new HashTableElement<T>(sourceChain[j].Key, value);

                        // add element to new chain with recalculated hash key
                        temp[hash].Add(elem);
                    }
                }
			}

			chains = temp;
		}

        private static void Normalize(ref int x, int min, int max)
        {
            x = x < min ? min :
                x > max ? max : x;
        }

        private async void Wait(T value)
        {
            // there is strong reference
            // so just wait storage time
            await Task.Delay(storageTime);
        }
        #endregion
    }
}
