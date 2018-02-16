using System;
using System.Runtime.Serialization;

namespace task1
{
    /// <summary>
    /// Indicates that current task is aborted.
    /// </summary>
    [Serializable]
    internal class AbortedException : Exception
    {
        public AbortedException() : base()
        {
        }

        public AbortedException(string message) : base(message)
        {
        }

        public AbortedException(string message, Exception innerException) : base(message, innerException)
        {
        }

        protected AbortedException(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}