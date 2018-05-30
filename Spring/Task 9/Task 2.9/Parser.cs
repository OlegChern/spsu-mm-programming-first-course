using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Parser
    {
        public static List<Command> SplitString(string str)
        {
            var commands = new List<Command>();

            var stringComands = str.Split('|');

            foreach (var strCommand in stringComands)
            {
                var partsCommand = strCommand.Split(' ').ToList();
                int index = 0;
                while (index < partsCommand.Count)
                {
                    while (partsCommand[index].Length == 0)
                    {
                        partsCommand.RemoveAt(index);
                        if (index >= partsCommand.Count)
                        {
                            break;
                        }
                    }
                    index++;
                }
                if (partsCommand.Count == 0)
                {
                    throw new Exception("Ошибка: Неверно использован оператор \"|\" ...");
                }
                var commandName = partsCommand[0];
                List<string> arguments = new List<string>();

                if (partsCommand.Count > 1)
                {
                    partsCommand.RemoveAt(0);
                    arguments = partsCommand;
                }

                GetValuesVariables(arguments);

                IdentifyCommand(commandName, arguments, commands);
            }

            return commands;
        }

        private static void GetValuesVariables(List<string> args)
        {
            for (int i = 0; i < args.Count; i++)
            {
                if (args[i][0] == '$')
                {
                    var name = args[i].Remove(0, 1);
                    if (Bash.BashObject.Variables.Select((z) => z.Name).Contains(name))
                    {
                        foreach (var e in Bash.BashObject.Variables)
                        {
                            if (e.Name == name)
                            {
                                args[i] = e.Value;
                                break;
                            }
                        }                     
                    }
                    else
                    {
                        throw new Exception($"Ошибка: Переменная {name} не определена ...");
                    }
                }
            }
        }

        private static void IdentifyCommand(string name, List<string> args, List<Command> commands)
        {
            if (name[0] == '$')
            {
                name = name.Remove(0, 1);
                if (args[0] == "=")
                {
                    args.RemoveAt(0);
                    commands.Add(new Assign(name, args));
                }
                else
                {
                    throw new Exception("Ошибка: Неправильно использован оператор присваивания ...");
                }
            }
            else
            {
                switch (name)
                {
                    case "cat":
                        {
                            commands.Add(new Cat(args));
                            break;
                        }
                    case "echo":
                        {
                            commands.Add(new Echo(args));
                            break;
                        }
                    case "exit":
                        {
                            commands.Add(new Exit(args));
                            break;
                        }
                    case "pwd":
                        {
                            commands.Add(new Pwd(args));
                            break;
                        }
                    case "wc":
                        {
                            commands.Add(new Wc(args));
                            break;
                        }
                    default:
                        {
                            commands.Add(new SystemCommand(name, args));
                            break;
                        }
                }
            }
                
        }
    }
}
