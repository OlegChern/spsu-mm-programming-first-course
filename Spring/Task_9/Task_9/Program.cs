namespace Task_9
{
    class Program
    {
        static void Main(string[] args)
        {
            using (Interpreter interpreter = new Interpreter())
            {
                interpreter.Start();
            }
        }
    }
}
