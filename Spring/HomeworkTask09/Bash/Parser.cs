using System;
using System.Collections.Generic;
using Bash.Commands;

namespace Bash
{
    static class Parser
    {
        public static List<ICommand> Parse(string str)
        {
            List<ICommand> commands = new List<ICommand>();

            if (str.Length == 0)
            {
                return commands;
            }

            string[] splittedCommands = str.Split('|');

            for (int i = 0; i < splittedCommands.Length; i++)
            {
                if (splittedCommands[i].Length == 0)
                {
                    continue;
                }

                // if first symbols are empty delete them
                RemoveEmptyBeginning(ref splittedCommands[i]);

                // split by space symbol
                string[] parts = splittedCommands[i].Split(' ');

                if (parts.Length == 0)
                {
                    continue;
                }

                // process assigning
                if (ProcessAssigning(splittedCommands[i], commands))
                {
                    continue;
                }

                // for decoding varibles, e.g. $a
                string argument = string.Empty;

                foreach (string part in parts)
                {
                    if (part.Length == 0)
                    {
                        continue;
                    }

                    // process using
                    ProcessUsing(part, ref argument);
                }

                // if can't parse
                if (!ProcessCommand(parts[0], argument, splittedCommands[i], commands))
                {
                    commands.Add(new SystemProcess(Concatenate(0, parts.Length, parts)));
                }
            }

            return commands;
        }

        private static void RemoveEmptyBeginning(ref string str)
        {
            int removeCount = 0;

            while (str[removeCount] == ' ')
            {
                removeCount++;
            }

            if (removeCount > 0)
            {
                str = str.Remove(0, removeCount);
            }
        }

        private static void ProcessUsing(string part, ref string argument)
        {
            if (part[0] == '$')
            {
                // remove '$'
                string newPart = part.Remove(0, 1);

                if (!newPart.Contains("="))
                {
                    // use variable
                    Bash.Instance.Variables.GetValue(newPart, out argument);
                }
            }
        }

        private static bool ProcessAssigning(string part, List<ICommand> commands)
        {
            if (part[0] == '$')
            {
                // remove '$'
                string newPart = part.Remove(0, 1);

                if (newPart.Contains("="))
                {
                    // if contains then add split by '='
                    // and add to variables list
                    return SplitAssigning(newPart, commands);
                }
            }

            return false;
        }

        private static bool SplitAssigning(string str, List<ICommand> commands)
        {
            string[] splittedPart = str.Split('=');

            // must be 2 parts: ..=..
            if (splittedPart.Length == 2)
            {
                // if name is not empty
                if (splittedPart[0].Length > 0)
                {
                    // add variable
                    commands.Add(new Assign(splittedPart[0], splittedPart[1]));

                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// Try to process command
        /// </summary>
        /// <param name="expression">expression to process</param>
        /// <param name="argument">decoded variable, e.g. $a</param>
        /// <param name="command">full command string</param>
        /// <param name="commands">list of commands</param>
        /// <returns>processing status</returns>
        private static bool ProcessCommand(string expression, string argument, string command, List<ICommand> commands)
        {
            switch (expression)
            {
                case "echo":
                    {
                        if (argument.Length == 0)
                        {
                            argument = command.Remove(0, expression.Length + 1);
                        }

                        commands.Add(new Echo(argument));
                        return true;
                    }
                case "exit":
                    {
                        commands.Add(new Exit());
                        return true;
                    }
                case "pwd":
                    {
                        commands.Add(new Pwd());
                        return true;
                    }
                case "cat":
                    {
                        commands.Add(new Cat(argument));
                        return true;
                    }
                case "wc":
                    {
                        commands.Add(new Wc(argument));
                        return true;
                    }
            }

            return false;
        }

        /// <summary>
        /// Concatenates string arrays
        /// </summary>
        private static string Concatenate(int startIndex, int endIndex, string[] strs)
        {
            string result = string.Empty;

            for (int i = startIndex; i < endIndex; i++)
            {
                result += strs[i];
            }

            return result;
        }
    }
}
