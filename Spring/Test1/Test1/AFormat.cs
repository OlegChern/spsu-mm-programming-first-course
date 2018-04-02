namespace Test1
{
    public abstract class AFormat<T>
    {
        public T value;

        public abstract T First { get; }

        public abstract T Second { get; }

        public AFormat(T value)
        {
            this.value = value;
        }

        public abstract string Format(FormattingType formattingType);
    }
}
