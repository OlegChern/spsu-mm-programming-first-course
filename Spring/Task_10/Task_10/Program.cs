using Unity;
using BlackjackClassesLib;
using Unity.Injection;

namespace Task_10
{
    class Program
    {
        static void Main(string[] args)
        {
            UnityContainer container = new UnityContainer();
            container.RegisterSingleton<Game>(new InjectionConstructor(8));
            Game thisGame = container.Resolve<Game>();
            container.RegisterType<Bot>(new InjectionConstructor(500.0, thisGame.GameDeck, 30, 17, true,false));
            Bot first = container.Resolve<Bot>();
            container.RegisterType<Bot>(new InjectionConstructor(500.0, thisGame.GameDeck, 25, 16, false, true));
            Bot second = container.Resolve<Bot>();
            thisGame.PlayGame(first,second);
        }
    }
}
