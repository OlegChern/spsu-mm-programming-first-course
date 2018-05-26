using System;
using System.Collections.Generic;

namespace Bash
{
    public class Bash
    {
        #region fields
        private bool isExecuting;

        private IPrinter printer;
        private IReader reader;
        private Context context;
        private VariableContainer variables;

        private static Bash instance;
        #endregion

        #region properties
        /// <summary>
        /// Current instance
        /// </summary>
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

        /// <summary>
        /// Class for reading
        /// </summary>
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

        /// <summary>
        /// Class for printing
        /// </summary>
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
        #endregion

        #region constructor
        private Bash()
        {
            isExecuting = false;

            context = new Context();
            variables = new VariableContainer();
        }
        #endregion

        #region main
        /// <summary>
        /// Start using Bash
        /// </summary>
        /// <param name="printer">class for printing</param>
        /// <param name="reader">class for reading</param>
        public void Start(IPrinter printer, IReader reader)
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

        /// <summary>
        /// Stop using Bash
        /// </summary>
        public void Stop()
        {
            isExecuting = false;
        }
        #endregion

        #region additional
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
        #endregion
    }
}
