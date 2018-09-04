namespace Task5.Chat
{
    class Program
    {
        static void Main(string[] args)
        {
            Client client = Connection.CreateClient();
            Connection.Chat(client);
        }
    }
}
