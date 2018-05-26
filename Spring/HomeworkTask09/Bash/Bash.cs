using System;
using System.Collections.Generic;
using Bash.Printing;

namespace Bash
{
    public class Bash
    {
        private bool isExecuting;

        private IPrinter printer;
        private IReader reader;
        private Context context;
        private VariableContainer variables;

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

        public IReader Reader
        {
            get
            {
                return reader;
            }
            set
            {
                reader = value;
            }
        }

        public IPrinter Printer
        {
            get
            {
                return printer;
            }
            set
            {
                printer = value;
            }
        }

        internal VariableContainer Variables
        {
            get
            {
                return variables;
            }
        }

        private Bash()
        {
            isExecuting = false;

            ConsoleUserInterface ui = new ConsoleUserInterface();
            printer = ui;
            reader = ui;

            context = new Context();
            variables = new VariableContainer();
        }

        private Bash(IPrinter printer, IReader reader)
        {
            isExecuting = false;

            this.printer = printer;
            this.reader = reader;

            context = new Context();
            variables = new VariableContainer();
        }

        public void Start()
        {
            printer.Print("Bash started.");
            ShowHelp();

            isExecuting = true;

            while (isExecuting)
            {
                try
                {
                    string str = reader.Read();

                    List<ICommand> commands = Parser.Parse(str);
                    
                    foreach(ICommand command in commands)
                    {
                        context.SetCommand(command);
                        context.ExecuteCommand();
                    }
                }
                catch (Exception ex)
                {
                    printer.Print("> " + ex.Message);
                }
            }
        }

        public void Stop()
        {
            isExecuting = false;
        }

        private void ShowHelp()
        {
            printer.Print("Commands:");
            printer.Print("  echo - show argument(-s)");
            printer.Print("  exit - stop Bash");
            printer.Print("  pwd - show current directory");
            printer.Print("  cat[FILENAME] - show file content");
            printer.Print("  wc[FILENAME] - show number of strings, words and bytes");

            printer.Print("Operators:");
            printer.Print("  $ - assigning and using of local variables");
            printer.Print("  | - commmands pipelining");
        }
    }
}
