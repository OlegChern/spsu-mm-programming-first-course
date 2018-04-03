using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2
{
    public struct TanksArmor
    {
        public TanksArmor(int front, int sides, int rear)
        {
            _front = front;
            _sides = sides;
            _rear = rear;
        }

        public void WriteInfo()
        {
            Console.WriteLine("Front: {0} mm Sides: {1} mm Rear: {2} mm", _front, _sides, _rear);

        }
        private readonly int _front;
        private readonly int _sides;
        private readonly int _rear;
    }
}
