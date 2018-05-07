using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Interface;

namespace Task8
{
    class Program
    {
        static void Main(string[] args)
        {
            IEnumerable<Type> collectionTypes = null;
            bool correctLocation = false;
            while (!correctLocation)
            {
                Console.WriteLine("Please, enter the location of the file");
                string location = Console.ReadLine();
                try
                {
                    collectionTypes = Assembly.LoadFile(location).ExportedTypes;
                }
                catch
                {
                    Console.WriteLine("Incorrect location");
                    continue;
                }
                correctLocation = true;
            }

            var collectionSuitableTypes = from temp in collectionTypes
                                          where temp.GetInterfaces().Contains(typeof(TempInterface))
                                          select temp;

            var collectionConstructors = from temp in collectionSuitableTypes
                                         select temp.GetConstructor(new Type[0]);

            var collectionObjects = from temp in collectionConstructors
                                    select (TempInterface)temp.Invoke(new object[0]);

            foreach (var temp in collectionObjects)
            {
                temp.DoSomething();
            }
        }
    }
}
