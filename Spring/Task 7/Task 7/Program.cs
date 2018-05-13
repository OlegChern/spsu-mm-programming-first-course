using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using WeakHashtable;

namespace Program
{
    class Program
    {
        static void Main(string[] args)
        {
            var hashTable = new WeakHashTable<TestClass>(4, 3, 2000);

            hashTable.Print();

            Console.WriteLine("Добавление элементов:");
            hashTable.SetValue("Ключ", new TestClass());
            hashTable.SetValue("Собака", new TestClass());
            hashTable.SetValue("Монета", new TestClass());
            hashTable.SetValue("Стол", new TestClass());
            hashTable.SetValue("Стул", new TestClass());
            hashTable.SetValue("Задача", new TestClass());
            hashTable.Print();

            Console.WriteLine("Перебалансировка таблицы:");
            hashTable.SetValue("qwerty", new TestClass());
            hashTable.SetValue("1234", new TestClass());
            hashTable.SetValue("wasd", new TestClass());
            hashTable.SetValue("GGGGG", new TestClass());
            hashTable.SetValue("777", new TestClass());
            hashTable.SetValue("****", new TestClass());
            hashTable.Print();

            Console.WriteLine("Переопределение значений: qwerty, 1234 и ****");
            hashTable.SetValue("qwerty", new TestClass());
            hashTable.SetValue("1234", new TestClass());
            hashTable.SetValue("****", new TestClass());
            hashTable.Print();

            Console.WriteLine("Удаление элементов: Собака и Стол");
            hashTable.Remove("Собака");
            hashTable.Remove("Стол");
            hashTable.Print();

            Console.WriteLine("Поиск элементов: Ключ, Кошка, wasd и Стол");
            Console.WriteLine("Элемент по ключу \"Ключ\": {0}", hashTable.ContainsKey("Ключ"));
            Console.WriteLine("Элемент по ключу \"Кошка\": {0}", hashTable.ContainsKey("Кошка"));
            Console.WriteLine("Элемент по ключу \"wasd\": {0}", hashTable.ContainsKey("wasd"));
            Console.WriteLine("Элемент по ключу \"Стол\": {0}", hashTable.ContainsKey("Стол"));
        }
    }
}
