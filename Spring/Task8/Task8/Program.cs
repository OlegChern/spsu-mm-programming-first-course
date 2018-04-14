using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using Template;

namespace Task8
{
    static class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Please, specify a *.dll address.");
                return;
            }

            if (args.Length > 1)
            {
                Console.WriteLine("Error: too many arguments given.");
                return;
            }

            try
            {
                var assembly = Assembly.LoadFile(args[0]);

                var allTypes = assembly.ExportedTypes.ToList();
                
                
                var doers =
                    from type in assembly.ExportedTypes
                    where typeof(IDoer).IsAssignableFrom(type)
                    from constructor in type.GetTypeInfo().DeclaredConstructors
                    where constructor.GetParameters().Length == 0
                    select (IDoer) constructor.Invoke(new object[] { });

                foreach (var doer in doers)
                {
                    doer.Do();
                }
            }
            catch
            {
                Console.WriteLine("Error");
            }
        }
    }
}
