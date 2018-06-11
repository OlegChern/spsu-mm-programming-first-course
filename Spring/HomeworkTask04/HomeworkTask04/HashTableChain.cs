using System;
using System.Collections.Generic;

namespace HashTable
{
    internal class HashTableChain<T>
    {
        #region fields
        private HashTableElement<T> rootElement;
        private int chainSize;
        #endregion

        #region properties
        internal int ChainSize
        {
            get
            {
                return chainSize;
            }
        }

        internal HashTableElement<T> this[int index]
        {
            get
            {
                if (index >= 0 && index < chainSize)
                {
                    HashTableElement<T> current = rootElement;

                    for (int i = 0; i < index; i++)
                    {
                        current = current.Next;
                    }

                    return current;
                }

                return null;
            }
        }
        #endregion

        #region constructor
        internal HashTableChain()
        {
            chainSize = 0;
        }
        #endregion

        #region methods
        internal void Add(HashTableElement<T> element)
        {
            chainSize++;

            if (rootElement == null)
            {
                rootElement = element;
                return;
            }

            HashTableElement<T> current = rootElement;

            while (current.Next != null)
            {
                current = current.Next;
            }

            current.Next = element;
        }

        internal HashTableElement<T> Find(string key)
        {
            if (rootElement == null)
            {
                return null;
            }

            if (rootElement.Key == key)
            {
                return rootElement;
            }

            HashTableElement<T> current = rootElement;

            while (current.Next != null)
            {
                if (current.Key == key)
                {
                    return current;
                }

                current = current.Next;
            }

            return null;
        }

        // remove element and fix links
        internal void Remove(string key)
        {
            if (rootElement == null)
            {
                return;
            }

            if (rootElement.Key == key)
            {
                if (rootElement.Next != null)
                {
                    rootElement = rootElement.Next;
                }
                else
                {
                    rootElement = null;
                    chainSize--;

                    return;
                }
            }

            HashTableElement<T> current = rootElement;

            while (current.Next != null)
            {
                if (current.Next.Key == key)
                {
                    current.Next = current.Next.Next;
                    chainSize--;

                    return;
                }

                current = current.Next;
            }

            #endregion
        }
    }
}
