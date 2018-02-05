using System.Collections.Generic;

namespace task4
{
    interface ILinkedList<T> : IEnumerable<T>
    {
        uint Length { get; }
        void AddToStart(T value);
        void AddToEnd(T value);
        bool Remove(T value);
        ListElement<T> PopFirst();
        ListElement<T> PopLast();
        bool Contains(T value);
    }
}
