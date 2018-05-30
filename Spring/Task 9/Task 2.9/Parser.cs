using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Parser
    {
        public static List<Command> SplitString(string str, Bash interpretator)
        {
            var commands = new List<Command>();

            var stringComands = new string[1] { str };

            bool isPipe = false;

            if (str.Contains('|'))
            {
                stringComands = str.Split('|');
                isPipe = true;
            }

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
                    if (isPipe)
                    {
                        throw new Exception("Ошибка: Неверно использован оператор \"|\" ...");
                    }
                    continue;
                }
                var commandName = partsCommand[0];
                List<string> arguments = new List<string>();

                if (partsCommand.Count > 1)
                {
                    partsCommand.RemoveAt(0);
                    arguments = partsCommand;
                }

                GetValuesVariables(arguments, interpretator);

                IdentifyCommand(commandName, arguments, commands, interpretator);
            }

            return commands;
        }

        private static void GetValuesVariables(List<string> args, Bash interpretator)
        {
            for (int i = 0; i < args.Count; i++)
            {
                if (args[i][0] == '$')
                {
                    var name = args[i].Remove(0, 1);
                    if (interpretator.Variables.Select((z) => z.Name).Contains(name))
                    {
                        foreach (var e in interpretator.Variables)
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

        private static void IdentifyCommand(string name, List<string> args, List<Command> commands, Bash interpretator)
        {
            if (name[0] == '$')
            {
                name = name.Remove(0, 1);
                if (name.Contains('='))
                {
                    var strings = name.Split('=');
                    name = strings[0];
                    if ((args.Count != 0) || (strings.Length != 2))
                    {
                        throw new Exception("Ошибка: Не удалось присвоить данное значение ...");
                    }
                    args.Add(strings[1]);
                    commands.Add(new Assign(name, args, interpretator));
                }
                else
                {
                    if (args[0] == "=")
                    {
                        args.RemoveAt(0);
                        commands.Add(new Assign(name, args, interpretator));
                    }
                    else
                    {
                        throw new Exception("Ошибка: Неправильно использован оператор присваивания ...");
                    }
                }
            }
            else
            {
                switch (name)
                {
                    case "cat":
                        {
                            commands.Add(new Cat(args, interpretator));
                            break;
                        }
                    case "echo":
                        {
                            commands.Add(new Echo(args, interpretator));
                            break;
                        }
                    case "exit":
                        {
                            commands.Add(new Exit(args, interpretator));
                            break;
                        }
                    case "pwd":
                        {
                            commands.Add(new Pwd(args, interpretator));
                            break;
                        }
                    case "wc":
                        {
                            commands.Add(new Wc(args, interpretator));
                            break;
                        }
                    default:
                        {
                            commands.Add(new SystemCommand(name, args, interpretator));
                            break;
                        }
                }
            }
                
        }
    }
}
