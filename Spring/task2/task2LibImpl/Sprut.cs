using task2Lib;

using static task2Lib.Util;

namespace task2LibImpl
{
    public class Sprut : AbstractTank
    {
        public double MachineGun { get; }

        public Sprut():
            base("Sprut-SD", "Russia", 18, 3.1, 9.7, 125, 70)
        {
            MachineGun = 7.62;
        }

        public override string GetFullInfo() =>
            base.GetFullInfo() +
            $"Machine gun calber: {MachineGun} mm{n}";
    }
}
