using System;
using System.Threading;

namespace Task7.WeakReference
{
    public class TestClass
    {
        public string Name;
        public TestClass(string name)
        {
            Name = name;
        }
        public override string ToString()
        {
            return Name;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            HashTable<TestClass> hashTable = new HashTable<TestClass>(3, 1000);

            Console.WriteLine("Add keys 1, 2, 3, 4, 5");
            hashTable.AddElement(1, new TestClass("a"));
            hashTable.AddElement(2, new TestClass("b"));
            hashTable.AddElement(3, new TestClass("c"));
            hashTable.AddElement(4, new TestClass("d"));
            hashTable.AddElement(5, new TestClass("e"));
            hashTable.Print();

            Console.WriteLine("Value of 1 == {0}", hashTable.GetValueByKey(1));
            Console.WriteLine();

            Console.WriteLine("Delete keys 2, 3");
            hashTable.DeleteElement(2);
            hashTable.DeleteElement(3);
            hashTable.Print();

            Console.WriteLine("Garbage collection");
            GC.Collect();
            hashTable.Print();

            Console.WriteLine("After 1500 milliseconds");
            Thread.Sleep(1500);
            GC.Collect();
            hashTable.Print();
        }
    }
}
