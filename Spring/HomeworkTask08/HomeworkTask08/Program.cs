using System;
using System.IO;
using System.Reflection;
using LibraryInterface;

namespace Plagin
{
    class Program
    {
        static void Main(string[] args)
        {
            // get path
            string path;
            if (args.Length > 0)
            {
                path = args[0];
            }
            else if (args.Length == 0)
            {
                Console.WriteLine("Enter path to .dll that implements INameable inteface: ");
                path = Console.ReadLine();
            }
            else
            {
                Console.WriteLine("Enter path to .dll that implements INameable inteface as argument.");
                return;
            }

            // check existance
            if (!File.Exists(path))
            {
                Console.WriteLine("File not found.");
                return;
            }

            Assembly assembly = Assembly.LoadFrom(path);
            
            // for each public type
            foreach(Type type in assembly.GetExportedTypes())
            {
                // is class and implements interface
                if (type.IsClass && typeof(INameable).IsAssignableFrom(type))
                {
                    // create instance of this type
                    INameable nameable = (INameable)Activator.CreateInstance(type);

                    // get name
                    string name = nameable.GetName();

                    // print it
                    Console.WriteLine(name);

                    return;
                }
            }

            Console.WriteLine("Class not found.");
        }
    }
}
