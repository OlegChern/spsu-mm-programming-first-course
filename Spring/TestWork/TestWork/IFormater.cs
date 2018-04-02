namespace TestWork
{
    public interface IFormater<T>
    {
        FormatMode Mode { get; }
        string Format(T t);
    }
}
