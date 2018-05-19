using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bash
{
    struct Variable
    {
        string name;
        string value;

        public string Name
        {
           get
            {
                return name;
            }
        }

        public string Value
        {
            get
            {
                return value;
            }
        }

        public Variable(string name, string value)
        {
            this.name = name;
            this.value = value;
        }
    }
}
