namespace Program
{
    class Program
    {
        static void Main(string[] args)
        {
            // create instance of user interface
            ConsoleUserInterface ui = new ConsoleUserInterface();

            // start
            Bash.Bash.Instance.Start(ui, ui);
        }
    }
}
