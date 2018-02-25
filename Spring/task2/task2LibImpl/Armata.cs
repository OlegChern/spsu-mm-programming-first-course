using task2Lib;

using static task2Lib.Util;

namespace task2LibImpl
{
    public class Armata : AbstractTank
    {
        public double MachineGun1 { get; } // mm
        public double MachineGun2 { get; } // mm

        public Armata():
            base("Armata", "Russia", 48, 3.5, 10.8, 125, 80)
        {
            MachineGun1 = 12.7;
            MachineGun2 = 7.62;
        }

        public override string GetFullInfo() =>
            base.GetFullInfo() +
            $"First machine gun caliber: {MachineGun1} mm{n}" +
            $"Second machine gun caliber: {MachineGun2} mm{n}";
    }
}
