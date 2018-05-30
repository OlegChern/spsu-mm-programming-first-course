﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    public abstract class Command
    {
        public Bash Interpretator { get; protected set; }

        public Command(Bash interpretator)
        {
            Interpretator = interpretator;
        }

        public List<string> Arguments { get; set; }

        public abstract void Execute();

        public abstract List<string> ExecutePipe();
    }
}
