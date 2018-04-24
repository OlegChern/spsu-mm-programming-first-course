using System;
using System.Collections.Generic;
using Task9.Parsing;

namespace Task9.Tokenization
{
    public sealed class CommandToken : Token
    {
        public override TokenType TokenType => TokenType.Command;
        public override object Value => Command;

        public Command Command { get; }

        public override object Execute(IEnumerable<object> args, Context context, ExecutionType executionType)
        {
            switch (Command)
            {
                case Command.Echo:
                    return Executer.Echo(args);
                case Command.Exit:
                    return Executer.Exit();
                case Command.Pwd:
                    return Executer.Pwd(args, context);
                case Command.Cat:
                    return Executer.Cat(args, context);
                case Command.Wc:
                    return Executer.Wc(args, context);
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        public CommandToken(Command command)
        {
            Command = command;
        }
    }
}
