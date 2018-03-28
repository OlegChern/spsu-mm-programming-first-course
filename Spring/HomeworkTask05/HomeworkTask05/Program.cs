using System;

namespace Chat
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
