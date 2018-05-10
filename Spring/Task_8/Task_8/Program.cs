using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using Interfaces;

namespace Task_8
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                IEnumerable<Type> typesList = Assembly.LoadFile(args[0]).ExportedTypes;
                
                IEnumerable<Type> neenedTypesList =
                    from type in typesList
                    where type.GetInterfaces().Contains(typeof(ITest))
                    select type;

                IEnumerable<ConstructorInfo> constructorsList =
                    from type in neenedTypesList
                    select type.GetConstructor(new Type[0]);

                IEnumerable<ITest> objectsList =
                    from constructor in constructorsList
                    select (ITest) constructor.Invoke(new object[0]);

                foreach (var obj in objectsList)
                {
                    obj.PrintInfo();
                }
            }

            catch (IOException e)
            {
                Console.WriteLine("Incorrect input!");
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
