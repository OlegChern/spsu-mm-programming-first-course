using System;
using System.Collections.Generic;
using System.Reflection;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Interface;

namespace Program
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Пожалуйста, введите путь к библиотеке");
                return;
            }
            else if (args.Length > 1)
            {
                Console.WriteLine("Ошибка ввода! Попробуйте еще раз");
                return;
            }

            if (!File.Exists(args[0]))
            {
                Console.WriteLine("Файл по указанному пути не найден");
                return;
            }

            var assembly = Assembly.LoadFrom(args[0]);

            var listObjects = new List<IPrintable>();

            foreach (var type in assembly.GetExportedTypes())
            {
                if ((type.IsClass) && (type.GetInterfaces().Contains(typeof(IPrintable))))
                {
                    var obj = (IPrintable)Activator.CreateInstance(type);
                    obj.Print();
                    listObjects.Add(obj);
                }
            }
            if (listObjects.Count == 0)
            {
                Console.WriteLine("Классов реализующих интерфейс IPrintable в данной библиотеке не найдено!");
            }
        }
    }
}
