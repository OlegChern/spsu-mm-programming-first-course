using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2._4
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine("Создание листа интов.");

            var list1 = new DoublyLinkedList<int>();

            list1.Print();

            Console.WriteLine("Добавление элементов с конца.");

            for (int i = 0; i < 7; i++)
            {
                list1.Add(i);
            }

            list1.Print();

            Console.WriteLine("Добавление элементов с начала.");

            for (int i = 3; i < 6; i++)
            {
                list1.AddFirst(i);
            }

            list1.Print();

            Console.WriteLine("Удаление элементов 2, 4 и 4");

            list1.Remove(2);
            list1.Remove(4);
            list1.Remove(4);

            list1.Print();

            Console.WriteLine("Изменение значений по индексу.");

            list1[4] = 66;
            list1[6] = 128;

            list1.Print();

            Console.WriteLine("Получение значения по индексу.");

            int Value = 0;
            Console.Write("Value = {0} , Value = list1[6] , ", Value);
            Value = list1[6];
            Console.WriteLine("Value = {0}", Value);

            Console.WriteLine("Удаление всех элементов.");

            list1.Clear();

            list1.Print();

            Console.WriteLine("Создание списка строк");
            var list2 = new DoublyLinkedList<string>();

            list2.Print();

            Console.WriteLine("Добавление элементов");

            list2.Add("Середина");
            list2.Add("Конец");
            list2.AddFirst("Начало");

            list2.Print();

            Console.WriteLine("Поиск до и после удаления элемента:");

            list2.Print();

            Console.WriteLine("Поиск Середина: {0}", list2.Contains("Середина"));

            Console.WriteLine("Удаление.");

            list2.Remove("Середина");

            list2.Print();

            Console.WriteLine("Поиск Середина: {0}", list2.Contains("Середина"));

        }
    }
}
