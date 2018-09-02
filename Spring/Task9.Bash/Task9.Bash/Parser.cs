using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task9.Bash
{
    public static class Parser
    {
        public static List<string> ConvertArguments(List<string> arguments, Dictionary<string, string> variables)
        {
            List<string> newArguments = new List<string>();
            for (int i = 0; i < arguments.Count; i++)
            {
                string[] words = arguments[i].Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                for (int j = 0; j < words.Length; j++)
                {
                    string word = words[j].Trim();
                    if (word[0] == '$')
                    {
                        string variable;
                        if (variables.TryGetValue(word, out variable))
                        {
                            words[j] = variable;
                        }
                        else
                        {
                            throw new ArgumentException("incorrect argument '" + arguments[i] + "'");
                        }
                    }
                }
                newArguments.AddRange(words);
            }
            return newArguments;
        }

        private static ICommand NewCommand(string inputString, Dictionary<string, string> variables, bool isFirst)
        {
            string inputWithoutSpaces = inputString.Trim();
            string[] words = inputWithoutSpaces.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

            if((!isFirst) && (words.Length != 1))
            {
                throw new ArgumentException("incorrect arguments in '" + inputString + "'");
            }
            List<string> arguments = new List<string>();
            string commandName = words[0];
            for(int i = 1; i < words.Length; i++)
            {
                arguments.Add(words[i]);
            }
            if(arguments.Count > 0)
            {
                arguments = ConvertArguments(arguments, variables);
            }

            switch(commandName)
            {
                case "echo":
                    {
                        Echo echo = new Echo(arguments);
                        return echo;
                    }
                case "exit":
                    {
                        Exit exit = new Exit(arguments);
                        return exit;
                    }
                case "pwd":
                    {
                        Pwd pwd = new Pwd(arguments);
                        return pwd;
                    }
                case "cat":
                    {
                        Cat cat = new Cat(arguments);
                        return cat;
                    }
                case "wc":
                    {
                        Wc wc = new Wc(arguments);
                        return wc;
                    }
                default:
                    {
                        List<string> arg = new List<string>();
                        arg.Add(commandName);
                        arg.AddRange(arguments);
                        ProcessStart processStart = new ProcessStart(arg);
                        return processStart;
                    }
            }
        }

        private static AssignmentLocalVariable NewVariable(string inputString, Dictionary<string, string> variables, bool isFirst)
        {
            string inputWithoutSpaces = inputString.Trim();
            if(inputWithoutSpaces[0] != '$')
            {
                throw new ArgumentException("incorrect '" + inputString + "'");
            }
            string[] words = inputWithoutSpaces.Split(new char[] { '=' }, StringSplitOptions.RemoveEmptyEntries);

            if ((!isFirst) && (words.Length != 1))
            {
                throw new ArgumentException("incorrect '" + inputString + "'");
            }
            if ((words.Length == 2) && (isFirst))
            {
                return new AssignmentLocalVariable(new List<string>() { words[0], words[1] }, variables);
            }
            else if((!isFirst) && (words.Length == 1))
            {
                return new AssignmentLocalVariable(new List<string>() { words[0] }, variables);
            }
            else
            {
                throw new ArgumentException("incorrect '" + inputString + "'");
            }
        }

        public static List<ICommand> Parse(string inputString, Dictionary<string, string> variables)
        {
            List<ICommand> result = new List<ICommand>();
            string[] commands = inputString.Split(new char[] { '|' }, StringSplitOptions.RemoveEmptyEntries);

            if (commands[0].Contains('='))
            {
                result.Add(NewVariable(commands[0], variables, true));
            }
            else
            {
                ICommand newCommand = NewCommand(commands[0], variables, true);
                result.Add(newCommand);
            }

            try
            {
                for(int i = 1; i < commands.Length; i++)
                {
                    if (commands[i].Contains('='))
                    {
                        result.Add(NewVariable(commands[i], variables, false));
                    }
                    else
                    {
                        ICommand newCommand = NewCommand(commands[i], variables, false);
                        if (newCommand != null)
                        {
                            result.Add(newCommand);
                        }
                    }
                }
            }
            catch(ArgumentException exception)
            {
                Console.WriteLine(exception.Message);
                return null;
            }

            return result;
        }
    }
}
