using System;

namespace ControlWork
{
    abstract class AbstactClass<T> : IFormattable<T>
    {
        private T value;

        public T Value
        {
            get
            {
                return value;
            }
        }

        public AbstactClass(T value)
        {
            this.value = value;
        }

        public abstract string Format(T obj);
    }
}

