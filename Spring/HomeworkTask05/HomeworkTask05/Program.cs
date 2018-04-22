using Chat;

namespace HomeworkTask05
{
	class Program
	{
		static void Main()
		{
            UserInterface.ShowTutorial();

			Peer localPeer = new Peer();
			localPeer.Start();
		}
	}
}
