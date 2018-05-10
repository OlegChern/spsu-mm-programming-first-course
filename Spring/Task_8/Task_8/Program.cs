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
                string path = Console.ReadLine();

                IEnumerable<string> dllsList = Directory.EnumerateFiles(path, "*.dll");

                if (!dllsList.Any())
                {
                    Console.WriteLine("There are no dll files!");
                }
                else
                {
                    foreach (var dll in dllsList)
                    {

                        IEnumerable<Type> typesList = Assembly.LoadFile(dll).DefinedTypes;

                        List<Type> neenedTypesList = new List<Type>();
                        List<ConstructorInfo> constructorsList = new List<ConstructorInfo>();
                        List<ITest> objectsList = new List<ITest>();

                        foreach (Type type in typesList)
                        {
                            if (type.GetInterfaces().Contains(typeof(ITest)))
                            {
                                neenedTypesList.Add(type);
                            }
                        }


                        foreach (Type type in neenedTypesList)
                        {
                            if (type.GetConstructor(new Type[0]) != null)
                            {
                                constructorsList.Add(type.GetConstructor(new Type[0]));
                            }
                        }


                        foreach (ConstructorInfo constructor in constructorsList)
                        {
                            objectsList.Add((ITest)constructor.Invoke(new object[0]));
                        }
                        /*
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
                        */

                        foreach (var obj in objectsList)
                        {
                            obj.PrintInfo();
                        }
                    }
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

            Console.ReadKey();
        }
    }
}