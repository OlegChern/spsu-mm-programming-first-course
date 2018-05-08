using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractTank
{
    public abstract class Tank
    {
        public string Name { get; private set; }      // Название

        public string Country { get; private set; }   // Страна производитель

        public double Weight { get; private set; }    // Масса (т)

        public int Speed { get; private set; }        // Скорость (км/ч)

        public int Crew { get; private set; }         // Экипаж (человек)

        public int MainGun { get; private set; }      // Пушка (мм)

        public int PowerEngine { get; private set; }  // Мощность двигателя (л/с)

        public Tank(string name, string country, double weight, int speed, int crew, int mainGun, int powerEngine)
        {
            Name = name;
            Country = country;
            Weight = weight;
            Speed = speed;
            Crew = crew;
            MainGun = mainGun;
            PowerEngine = powerEngine;
        }

        public virtual void GetInfo()
        {
            Console.WriteLine("\nНазвание: {0} \n"
                + "Страна производитель: {1} \n"
                + "Масса: {2} т \n"
                + "Скорость: {3} км/ч \n"
                + "Экипаж: {4} человек \n"
                + "Мощность двигателя: {5} л/с \n"
                + "Пушка: {6} мм"
                , Name, Country, Weight, Speed, Crew, PowerEngine, MainGun);
        }
    }
}
