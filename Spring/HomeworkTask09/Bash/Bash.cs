using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Bash
    {
        private bool isExecuting;
        private Context context;

        private static Bash instance;

        public static Bash Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new Bash();
                }

                return instance;
            }
        }

        private Bash()
        {
            isExecuting = false;
            context = new Context();
        }

        public void Start()
        {
            Console.WriteLine("Bash started.");
            ShowHelp();

            List<Variable> variables = new List<Variable>();

            isExecuting = true;

            while (isExecuting)
            {
                try
                {
                    string str = Console.ReadLine();

                    ICommand command;
                    if (Parser.Parse(str, out command))
                    {
                        context.SetCommand(command);
                        context.ExecuteCommand();
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("> " + ex.Message);
                }
            }
        }

        public void Stop()
        {
            isExecuting = false;
        }

        private void ShowHelp()
        {
            Console.WriteLine("Commands:");
            Console.WriteLine("  echo - show argument(-s)");
            Console.WriteLine("  exit - stop Bash");
            Console.WriteLine("  pwd - show current directory");
            Console.WriteLine("  cat[FILENAME] - show file content");
            Console.WriteLine("  wc[FILENAME] - show number of strings, words and bytes");

            Console.WriteLine("Operators:");
            Console.WriteLine("  $ - assigning and using of local variables");
            Console.WriteLine("  | - commmands pipelining");
        }
    }
}
