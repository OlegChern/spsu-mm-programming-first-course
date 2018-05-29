using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Task_9
{
    static class Parser
    {
        public static Instruction Parse(string inStr)
        {
            if (inStr.First() == '$')
            {
                try
                {
                    return GetVariableDefInstrucions(inStr);
                }
                catch (VariableDefException e)
                {
                    throw e;
                }
            }

            try
            {
                return GetCommandInstructions(inStr);
            }
            catch (CommandException)
            {
                return new Instruction(InstructionType.Command, new List<Command> { new Command(CommandType.CmdCommand,new List<string>{inStr}) });
            }
        }


        private static Instruction GetVariableDefInstrucions(string inStr)
        {
            StringBuilder builder = new StringBuilder(inStr);
            if (!IsCorrectDefinitionSyntax(inStr))
            {
                throw new VariableDefException("Incorrect definition syntax");
            }

            char[] charArrName = new char[inStr.IndexOf('=') - 1];
            builder.CopyTo(1, charArrName, 0, inStr.IndexOf('=') - 1);

            char[] charArrVal = new char[inStr.Length - inStr.IndexOf('=') - 1];
            builder.CopyTo(inStr.IndexOf('=') + 1, charArrVal, 0, inStr.Length - inStr.IndexOf('=') - 1);

            string strVal = new string(charArrVal);
            string strName = new string(charArrName);

            strName = strName.TrimEnd(' ');
            strVal = strVal.Trim();

            if (!IsCorrectVariableName(strName))
            {
                throw new VariableDefException("Incorrect variable name");
            }

            if (Int32.TryParse(strVal, out int intResult))
            {
                return new Instruction(InstructionType.VariableDef, strName, intResult);
            }

            if (Double.TryParse(strVal, out double doubleResult))
            {
                return new Instruction(InstructionType.VariableDef, strName, doubleResult);
            }

            return new Instruction(InstructionType.VariableDef, strName, strVal);
        }

        private static bool IsCorrectDefinitionSyntax(string inStr) =>
            inStr.Contains('=') && (inStr.LastIndexOf('=') == inStr.IndexOf('=')) &&
            inStr.IndexOf('=') != inStr.Length - 1;

        private static bool IsCorrectVariableName(string name) =>
            ((name[0] <= 'Z' && name[0] >= 'A') || (name[0] <= 'z' && name[0] >= 'a') || (name[0] == '_')) &&
            (name.All(c => !".,/';[](){}*&^%$#@!~`+=-\\|/<>!№:? ".Contains(c)));

        private static Instruction GetCommandInstructions(string inStr)
        {
            List<Command> resultCommands = new List<Command>();
            string[] commandsArr = inStr.Split(new[] {" | "}, StringSplitOptions.RemoveEmptyEntries);

            try
            {
                resultCommands.Add(GetCommand(commandsArr[0]));
            }
            catch (CommandException e)
            {
                throw e;
            }

            for (int i = 1; i < commandsArr.Length; ++i)
            {
                try
                {
                    resultCommands.Add(new Command(GetCommandType(commandsArr[i]),new List<string>()));
                }
                catch (CommandException e)
                {
                    throw e;
                }
            }

            return new Instruction(InstructionType.Command,resultCommands);
        }

        private static Command GetCommand(string command)
        {
            string[] wordsArr = command.Split(new[] { " " }, StringSplitOptions.RemoveEmptyEntries);
            try
            {
                CommandType commandType = GetCommandType(wordsArr[0]);
                List<string> commandArgs = new List<string>();
                for (int i = 1; i < wordsArr.Length ; ++i)
                {
                    commandArgs.Add(wordsArr[i]);
                }
                Command result = new Command(commandType, commandArgs);
                IsCorrectArgs(result);
                return result;
            }
            catch (CommandException e)
            {
                throw e;
            }
        }


        private static bool IsCorrectArgs(Command command)
        {
            switch (command.Type)
            {
                case CommandType.Pwd:
                {
                    if (command.Arguments.Count > 0)
                    {
                        throw new CommandException("Incorrect pwd command args");
                    }

                    return true;
                }
                case CommandType.Wc:
                {
                    if (command.Arguments.Count != 1)
                    {
                        throw new CommandException("Incorrect wc command args");
                    }

                    return true;
                }
                case CommandType.Cat:
                {
                    if (command.Arguments.Count != 1)
                    {
                        throw new CommandException("Incorrect cat command args");
                    }

                    return true;
                }
                case CommandType.Echo:
                {
                    return true;
                }
            }
            throw new CommandException("Incorrect command's args");
        }



        private static CommandType GetCommandType(string name)
        {
            name = name.ToLower();
            switch (name)
            {
                case "echo":
                {
                    return CommandType.Echo;
                }
                case "cat":

                {
                    return CommandType.Cat;
                }
                case "pwd":
                {
                    return CommandType.Pwd;
                }
                case "wc":

                {
                    return CommandType.Wc;
                }
                default:
                {
                    throw new CommandException("Incorrect command name");
                }
            }
        }


    }
}
