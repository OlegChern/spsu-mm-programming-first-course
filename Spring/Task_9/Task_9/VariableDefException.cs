using System;

namespace Task_9
{
    class VariableDefException : Exception
    {
        public override string Message { get; }

        public VariableDefException(string message)
        {
            Message = message;
        }
    }
}
