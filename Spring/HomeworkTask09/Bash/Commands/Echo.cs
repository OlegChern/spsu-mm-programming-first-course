namespace Bash.Commands
{
    /// <summary>
    /// Shows argument(-s)
    /// </summary>
    class Echo : ICommand
    {
        string argument;

        public Echo(string argument)
        {
            this.argument = argument;
        }

        public void Execute()
        {
            Bash.Instance.Printer.Print(argument);
        }
    }
}
