using System;

namespace Task9.Bash
{
    [Serializable]
    public class ExitException : Exception
    {
        public ExitException() { }
        public ExitException(string message) : base(message) { }
        public ExitException(string message, Exception inner) : base(message, inner) { }
        protected ExitException(
          System.Runtime.Serialization.SerializationInfo info,
          System.Runtime.Serialization.StreamingContext context) : base(info, context) { }
    }
}
