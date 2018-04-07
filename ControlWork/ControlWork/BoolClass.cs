using System;

namespace ControlWork
{
    class BoolClass : AbstactClass<bool>
    {
        public BoolClass() : base(false) { }
        public BoolClass(bool value) : base(value) { }

        /// <summary>
        /// Formats bool
        /// </summary>
        /// <param name="obj">bool to conjuct with initial value</param>
        /// <returns>logical conjuction of initial value and obj</returns>
        public override string Format(bool obj)
        {
            return (Value && obj).ToString();
        }
    }
}
