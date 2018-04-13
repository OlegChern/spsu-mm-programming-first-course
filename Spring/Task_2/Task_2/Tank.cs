namespace Task_2
{
    internal abstract class Tank
    {
        public string Name { get; set; }
        public TanksArmor Armor { get; set; }
        public string Country { get; set; } 
        public double Weight { get; set; }
        public int GunСaliber { get; set; }
        public int SpeedLimit { get; set; }
       
        public abstract void GetInfo();
    }
}
