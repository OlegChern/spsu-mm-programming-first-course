using System;
using System.Collections.Generic;

namespace Task9.Bash
{
    public class Bash
    {
        private Dictionary<string, string> variables;

        public Bash()
        {
            variables = new Dictionary<string, string>();
        }

        private void PrintInfo()
        {
            Echo.PrintInfo();
            Exit.PrintInfo();
            Pwd.PrintInfo();
            Cat.PrintInfo();
            Wc.PrintInfo();
            AssignmentLocalVariable.PrintInfo();
            Console.WriteLine("| - pipelining commands");
        }

        private void ExecuteCommands(List<ICommand> commands)
        {
            commands[0].Execute();
            List<string> output = commands[0].Output;
            for (int i = 1; i < commands.Count; i++)
            {
                commands[i].Arguments = Parser.ConvertArguments(output, variables);
                commands[i].Execute();
                output = commands[i].Output;
            }
        }

        public void Start()
        {
            PrintInfo();

            while (true)
            {
                List<ICommand> commands = null;
                try
                {
                    string input = Console.ReadLine();
                    commands = Parser.Parse(input, variables);
                }
                catch (ArgumentException exception)
                {
                    Console.WriteLine(exception.Message);
                    commands = null;
                }
                catch (Exception)
                {
                    commands = null;
                }
                if (commands != null)
                {
                    try
                    {
                        ExecuteCommands(commands);
                    }
                    catch (Exception exception)
                    {
                        Console.WriteLine(exception.Message);
                    }
                }
            }
        }
    }
}
