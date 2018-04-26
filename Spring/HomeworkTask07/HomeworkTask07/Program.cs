﻿using System;
using WeakHashTable;

namespace HomeworkTask07
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hash table test.");
            Console.WriteLine("Collision resolution: separate chaining with list head cells.");

            HashTable<TestClass> table = new HashTable<TestClass>(4);

            #region adding test
            Console.WriteLine("\nAdding elements...");
            table.Add("WADX", new TestClass());
            table.Add("EDSF", new TestClass());
            table.Add("ZXC", new TestClass());
            table.Add("ASDX", new TestClass());
            table.Add("ZXCV", new TestClass());
            table.Add("ASDF", new TestClass());
            table.Add("ZXCV", new TestClass());
            table.Add("ASDFDS", new TestClass());
            table.Add("ASDFWD", new TestClass());

            Console.WriteLine(table.ToString());
            #endregion

            #region rebalancing test
            Console.WriteLine("\nAdding and rebalancing elements...");

            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());
            table.Add("WASD", new TestClass());

            Console.WriteLine(table.ToString());
            #endregion

            #region removing test
            Console.WriteLine("\nRemoving elements with keys \"ASDFDS\" and \"ASDFWD\"...");

            table.Remove("ASDFDS");
            table.Remove("ASDFWD");

            Console.WriteLine(table.ToString());
            #endregion

            #region finding test
            string[] keys = { "ZXCV", "TEST" };

            foreach (string key in keys)
            {
                TestClass value;

                if (table.Find(key, out value))
                {
                    Console.WriteLine("Value of element with key \"" + key + "\": " + value);
                }
                else
                {
                    Console.WriteLine("Value of element with key \"" + key + "\" not found");
                }
            }
            #endregion
        }
    }
}
