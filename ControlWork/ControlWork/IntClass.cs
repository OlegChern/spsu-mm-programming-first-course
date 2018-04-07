using System;

namespace ControlWork
{
    class IntClass: AbstactClass<int>
    {
        public IntClass() : base(0) { }
        public IntClass(int value) : base(value) { }

        /// <summary>
        /// Formats integer
        /// </summary>
        /// <param name="obj">number to sum with initial value</param>
        /// <returns>sum of initial value and obj</returns>
        public override string Format(int obj)
        {
            if (obj >= 0)
            {
                return (Value + obj).ToString();
            }
            else
            {
                return (Value - obj).ToString();
            }
        }
    }
}
