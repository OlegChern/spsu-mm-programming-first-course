using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using Task9.Parsing;
using Task9.Tokenization;

namespace Task9
{
    static class Program
    {
        static void Main()
        {
            Assembly.Load("System, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089");
            var x =
                from assembly in AppDomain.CurrentDomain.GetAssemblies()
                from type in assembly.GetExportedTypes()
                where type.Name == "Process"
                select type;
            var process = x.First();
            Console.WriteLine(process.FullName);
            var methods = new List<MethodInfo>(
                from method in process.GetMethods(BindingFlags.Public | BindingFlags.Static)
                where method.GetParameters().Length == 0
                select method
            );
            Console.WriteLine(methods.Count);
            
            var handler = new CommandHandler();
            do
            {
                string input = Console.ReadLine();

                try
                {
                    handler.Handle(input);
                }
                catch (InvalidTokenException exception)
                {
                    Console.WriteLine($"Invalid token: '{exception.Message}'");
                }
                catch (InvalidSyntaxException exception)
                {
                    Console.WriteLine($"Syntax error: {exception.Message}");
                }
                catch (KeyNotFoundException exception)
                {
                    Console.WriteLine($"Read access to unknown variable: '{exception.Message}'");
                }
                catch (ExecutionFinishedException)
                {
                    return;
                }
                catch (NotImplementedException)
                {
                    Console.WriteLine("Not implemented");
                }
            }
            while (true);
        }
    }
}
