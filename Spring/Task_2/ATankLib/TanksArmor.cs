using System;

namespace ATankLib
{
    public struct TanksArmor
    {
        public int Front { get; set; }
        public int Sides { get; set; }
        public int Rear { get; set; }

        public TanksArmor(int front, int sides, int rear)
        {
            Front = front;
            Sides = sides;
            Rear = rear;
        }

        public void WriteInfo()
        {
            Console.WriteLine("Front: {0} mm Sides: {1} mm Rear: {2} mm", Front, Sides, Rear);
        }
    }
}
