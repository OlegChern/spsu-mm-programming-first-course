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

        /// <summary>
        /// Check existance of variable with given name
        /// </summary>
        /// <param name="varName">name of variable to check</param>
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

        /// <summary>
        /// Get variable with given name
        /// </summary>
        /// <param name="name">name of variable</param>
        /// <param name="variable">out variable</param>
        /// <returns>existance of variable</returns>
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

        /// <summary>
        /// Get value of variable with given name
        /// </summary>
        /// <param name="name">name of variable</param>
        /// <param name="value">out value of variable</param>
        /// <returns>existance of variable</returns>
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

        /// <summary>
        /// Adds variable to container
        /// </summary>
        public void Add(Variable variable)
        {
            variables.Add(variable);
        }
    }
}
