namespace task4
{
    internal class Element
    {
        private Element previous;
        private Element next;

        public Element Previous
        {
            get => previous;
            set
            {
                // TODO
            }
        }

        public Element Next
        {
            get => next;
            set
            {
                // TODO
            }
        }

        public Element(Element previous = null, Element next = null)
        {
            this.previous = previous;
            this.next = next;
        }
    }
}