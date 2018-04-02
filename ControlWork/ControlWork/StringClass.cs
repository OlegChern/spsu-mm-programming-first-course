using System;

namespace ControlWork
{
    class StringClass : AbstactClass<string>
    {        
        public StringClass() : base("Default") { }
        public StringClass(string value) : base(value) { }

        /// <summary>
        /// Formats string
        /// </summary>
        /// <param name="obj">sting to be formatted</param>
        /// <returns>formatted string</returns>
        public override string Format(string obj)
        {
            return Value + " -- " + obj + " ++";
        }
    }
}
