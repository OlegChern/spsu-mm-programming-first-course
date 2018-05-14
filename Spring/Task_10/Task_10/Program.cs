using System;
using BlackjackClassesLib;
using Unity;
using Microsoft.Practices.Unity.Configuration;
using Unity.Injection;

namespace Task_10
{
    class Program
    {
        static void Main(string[] args)
        {
            IUnityContainer container = new UnityContainer();
            container.LoadConfiguration();
            Game thisGame = container.Resolve<Game>();
            container.RegisterInstance("thisGameDeck",thisGame.GameDeck);
            Bot firstBot = container.Resolve<Bot>("firstBot");
            Bot secondBot = container.Resolve<Bot>("secondBot");
            thisGame.PlayGame(firstBot,secondBot);
        }
    }
}
