﻿using System;

namespace Chat
{
	class Program
	{
		static void Main(string[] args)
		{
			Peer localPeer = new Peer();
			localPeer.Start();
		}
	}
}
