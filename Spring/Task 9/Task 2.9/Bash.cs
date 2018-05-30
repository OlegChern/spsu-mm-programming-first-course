using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public class Bash
    {
        public List<Variable> Variables { get; set; }

        public bool IsRunning { get; set; }

        private static Bash bashObject;
        public static Bash BashObject
        {
            get
            {
                if (bashObject == null)
                {
                    bashObject = new Bash();
                }
                return bashObject;
            }
        }

        public Bash()
        {
            Variables = new List<Variable>();
            IsRunning = false;
        }

        public void Start()
        {
            Console.WriteLine("Bash started ...");
            IsRunning = true;
            while (IsRunning)
            {
                try
                {
                    var str = Console.ReadLine();
                    List<Command> commands = Parser.SplitString(str);
                    if (commands.Count == 0)
                    {
                        continue;
                    }
                    if (commands.Count == 1)
                    {
                        commands[0].Execute();
                    }
                    else
                    {
                        for (int i = 0; i < commands.Count - 1; i++)
                        {
                            commands[i + 1].Arguments = commands[i].ExecutePipe();
                        }
                        commands[commands.Count - 1].Execute();
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }
    }
}
