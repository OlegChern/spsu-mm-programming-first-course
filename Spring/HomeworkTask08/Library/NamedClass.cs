using LibraryInterface;

namespace Library
{
    public class NamedClass : INameable
    {
        private const string name = "IDDQD";

        public string GetName()
        {
            return name;
        }
    }
}
