using System;

namespace Bash.Commands
{
    /// <summary>
    /// Assigns new variable
    /// </summary>
    class Assign : ICommand
    {
        Variable variable;

        public Assign(string name, string value)
        {
            if (Bash.Instance.Variables.Contains(name))
            {
                throw new ArgumentException("Variable with name \""+ name +"\" already exists!");
            }

            variable = new Variable(name, value);
        }

        public void Execute()
        {
            Bash.Instance.Variables.Add(variable);
        }
    }
}
