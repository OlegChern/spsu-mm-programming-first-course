using System;

namespace ControlWork
{
    interface IFormattable<T>
    {
        string Format(T obj);
    }
}
