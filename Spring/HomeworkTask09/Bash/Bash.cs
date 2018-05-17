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
                    else
                    {
                        ProcessStartInfo info = new ProcessStartInfo();
                        info.FileName ="/k"+str ;
                        info.Arguments = str;
                        info.CreateNoWindow = true;
                        info.RedirectStandardOutput = true;
                        info.UseShellExecute = false;


                        Process.Start(info);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("> " + ex.ToString());
                }
            }
        }

        public void Stop()
        {
            isExecuting = false;
        }
    }
}
