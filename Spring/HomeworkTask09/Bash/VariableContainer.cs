using System.Collections.Generic;

namespace Bash
{
    class VariableContainer
    {
        private List<Variable> variables;

        public VariableContainer()
        {
            variables = new List<Variable>();
        }

        public bool Contains(string varName)
        {
            foreach (Variable var in variables)
            {
                if (var.Name == varName)
                {
                    return true;
                }
            }

            return false;
        }

        public bool GetVariable(string name, out Variable variable)
        {
            foreach(Variable var in variables)
            {
                if (var.Name == name)
                {
                    variable = var;
                    return true;
                }
            }

            variable = null;
            return false;
        }

        public bool GetValue(string name, out string value)
        {
            foreach (Variable var in variables)
            {
                if (var.Name == name)
                {
                    value = var.Value;
                    return true;
                }
            }

            value = string.Empty;
            return false;
        }

        public void Add(Variable variable)
        {
            variables.Add(variable);
        }
    }
}
