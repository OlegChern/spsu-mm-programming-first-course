using System.Collections.Generic;

namespace Task_9
{
    class Command
    {
        public CommandType Type { get; }
        public List<string> Arguments { get; }

        public Command(CommandType type, List<string> arguments)
        {
            Type = type;
            Arguments = arguments;
        }
    }
}
