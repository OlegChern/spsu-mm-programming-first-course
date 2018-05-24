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
            hashTable.SetValue("Ключ", new TestClass(2));
            hashTable.SetValue("Собака", new TestClass(3));
            hashTable.SetValue("Монета", new TestClass(4));
            hashTable.SetValue("Стол", new TestClass(5));
            hashTable.SetValue("Стул", new TestClass(1));
            hashTable.SetValue("Задача", new TestClass(4));
            hashTable.Print();
           
            Console.WriteLine("Перебалансировка таблицы:");
            hashTable.SetValue("qwerty", new TestClass(35));
            hashTable.SetValue("1234", new TestClass(45));
            hashTable.SetValue("wasd", new TestClass(23));
            hashTable.SetValue("GGGGG", new TestClass(15));
            hashTable.SetValue("777", new TestClass(46));
            hashTable.SetValue("****", new TestClass(33));
            hashTable.Print();
            
            Console.WriteLine("Переопределение значений: qwerty, 1234 и ****");
            hashTable.SetValue("qwerty", new TestClass(54));
            hashTable.SetValue("1234", new TestClass(34));
            hashTable.SetValue("****", new TestClass(9));
            hashTable.Print();

            Console.WriteLine("Удаление элементов: Собака и Стол");
            hashTable.Remove("Собака");
            hashTable.Remove("Стол");
            hashTable.Print();

            Console.WriteLine("Поиск элементов: Ключ, Кошка, wasd и Стол");
            Console.WriteLine("Элемент по ключу \"Ключ\": {0}", hashTable.ContainsKey("Ключ"));
            Console.WriteLine("Элемент по ключу \"Кошка\": {0}", hashTable.ContainsKey("Кошка"));
            Console.WriteLine("Элемент по ключу \"wasd\": {0}", hashTable.ContainsKey("wasd"));
            Console.WriteLine("Элемент по ключу \"Стол\": {0}\n", hashTable.ContainsKey("Стол"));

            Console.WriteLine("Хэш-таблица после сборки мусора, до истечения TimeStorage");
            GC.Collect();
            hashTable.Print();

            Thread.Sleep(3000);

            Console.WriteLine("Хэш-таблица после сборки мусора, после истечения TimeStorage");
            GC.Collect();
            hashTable.Print();
        }
    }
}
