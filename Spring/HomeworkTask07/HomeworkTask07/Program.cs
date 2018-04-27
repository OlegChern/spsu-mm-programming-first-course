using System;
using WeakHashTable;

namespace HomeworkTask07
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hash table test.");
            Console.WriteLine("Collision resolution: separate chaining with list head cells.");

            WeakHashTable<TestClass> table = new WeakHashTable<TestClass>(4, 8, 5000);
            
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

            table.Add("11111111", new TestClass());
            table.Add("1111112", new TestClass());
            table.Add("111122", new TestClass());
            table.Add("11222", new TestClass());
            table.Add("2222", new TestClass());
            table.Add("3311", new TestClass());
            table.Add("332", new TestClass());
            table.Add("3221", new TestClass());
            table.Add("341", new TestClass());
            table.Add("44", new TestClass());
            table.Add("53", new TestClass());
            table.Add("8", new TestClass());
            table.Add("71", new TestClass());
            table.Add("62", new TestClass());
            table.Add("41111", new TestClass());

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
