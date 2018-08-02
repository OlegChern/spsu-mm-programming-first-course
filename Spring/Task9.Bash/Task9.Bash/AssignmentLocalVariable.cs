using System;
using System.Collections.Generic;

namespace Task9.Bash
{
    public class AssignmentLocalVariable : ICommand
    {
        public string Name { get; }

        public List<string> Arguments { get; set; }

        public List<string> Output { get; }

        public Dictionary<string, string> Variables { get; private set; }

        public AssignmentLocalVariable(List<string> arguments, Dictionary<string, string> dictionary)
        {
            Arguments = arguments;
            if (arguments.Count == 1)
            {
                Name = arguments[0];
            }
            else if (arguments.Count == 2)
            {
                Name = arguments[0] + " = " + arguments[1];
            }
            Output = new List<string>();
            Variables = dictionary;
        }

        public static void PrintInfo()
        {
            Console.WriteLine("$ - assignment and use of local session variables");
        }

        public void Execute()
        {
            if (Arguments.Count != 2)
            {
                throw new ArgumentException("incorrect arguments in assignment of local session variables");
            }

            string localVariables = Arguments[0].Trim();
            string value = Arguments[1].Trim();
            string[] variables = localVariables.Split(new char[] { ',', ' ' }, StringSplitOptions.RemoveEmptyEntries);

            for (int i = 0; i < variables.Length; i++)
            {
                variables[i] = variables[i].Trim();
                if (variables[i][0] != '$')
                {
                    throw new ArgumentException("incorrect '" + Name + "'");
                }
            }

            for (int i = 0; i < variables.Length; i++)
            {
                try
                {
                    Variables.Add(variables[i], value);
                }
                catch(ArgumentException)
                {
                    Variables[variables[i]] = value;
                }
            }

            Output.Add(value);
        }
    }
}
