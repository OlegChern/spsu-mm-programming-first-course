using System;
using System.Collections.Generic;

namespace Task9.Bash
{
    public interface ICommand
    {
        string Name { get; }

        List<string> Arguments { get; set; }

        List<string> Output { get; }

        void Execute();
    }
}
