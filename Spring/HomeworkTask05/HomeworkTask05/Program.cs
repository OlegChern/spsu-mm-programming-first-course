using System;

namespace Chat
{
	class Program
	{
		static void Main()
		{
			Peer localPeer = new Peer();
			localPeer.Start();
		}
	}
}
