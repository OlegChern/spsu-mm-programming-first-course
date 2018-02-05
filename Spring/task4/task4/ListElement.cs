using System;

namespace task4
{
    internal class ListElement<T>
    {
        private ListElement<T> previous;
        private ListElement<T> next;
        // private T value;

        /* Setters automatically validate
         * and update corresponding references
         * of Element passed to them
         * 
         * Keep in mind that checks
         * they perform are not sufficient
         * to avoid data loss
         */

        public ListElement<T> Previous
        {
            get => previous;
            set
            {
                if (value == null)
                {
                    if (previous != null)
                        previous.next = null;

                    previous = null;
                    return;
                }

                if (value.next != null)
                    throw new ArgumentException();

                if (previous != null)
                    previous.next = null;

                previous = value;
                value.next = this;
            }
        }

        public ListElement<T> Next
        {
            get => next;
            set
            {
                if (value  == null)
                {
                    if (next != null)
                        next.previous = null;

                    next = null;
                    return;
                }

                if (value.previous != null)
                    throw new ArgumentException();

                if (next != null)
                    next.previous = null;

                next = value;
                value.previous = this;
            }
        }

        public T Value { get; set; }

        public ListElement(ListElement<T> previous = null, ListElement<T> next = null)
        {
            this.previous = previous;
            this.next = next;
        }
    }
}
