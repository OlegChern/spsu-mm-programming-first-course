using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_2
{
    abstract class Tank
    {
        protected string _country;
        protected double _weight;
        protected TanksArmor _armor;
        protected int _gun_сaliber;
        protected int _speed_limit;

        public string Country
        {
            get => _country;
            set => _country = value;
        }
        public double Weight
        {
            get => _weight;
            set => _weight = value;
        }
        public int Gun_сaliber
        {
            get => _gun_сaliber;
            set => _gun_сaliber = value;
        }
        public int Speed_limit
        {
            get => _speed_limit;
            set => _speed_limit = value;
        }

        public abstract void GetInfo();
    }
}
