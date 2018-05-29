using System.Collections.Generic;

namespace Task_9
{
    class Instruction
    {
        public InstructionType Type { get; }

        public string VariableName { get; }
        public object VariableValue { get; }
        
        public List<Command> Commands { get; }

        public Instruction(InstructionType type, List<Command> commandsList)
        {
            Type = type;
            Commands = commandsList;
        }

        public Instruction(InstructionType type, string variableName, object variableValue)
        {
            Type = type;
            VariableName = variableName;
            VariableValue = variableValue;
        }
    }
}
