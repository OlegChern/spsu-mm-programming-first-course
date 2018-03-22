using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
	public class Peer
	{
		#region constants
		private const int MessageLength = 256;
		private const int port = 8151;
		#endregion

		#region private properties
		private string name;
		private bool isRunning;

		//private Socket receiver;
		private Thread receivingThread;

		private List<IPEndPoint> connectedEp = new List<IPEndPoint>();
		#endregion

		#region public methods
		/// <summary>
		/// Creates new peer
		/// </summary>
		public Peer()
		{
			ReadName();
		}

		public void Start()
		{
			isRunning = true;

			SendMessage(name + " connected.");

			InitReceiver();
			Send();
		}
		#endregion

		// todo
		#region main methods
		private void InitReceiver()
		{
			// additional thread for receiving messages
			receivingThread = new Thread(new ThreadStart(Receive));
			receivingThread.IsBackground = true;
			receivingThread.Start();
		}

		private void Receive()
		{
			Socket receiver = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

			try
			{
				// get local end point
				IPEndPoint localEp = null;
				IPHostEntry ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());

				foreach (IPAddress ip in ipHostInfo.AddressList)
				{
					if (ip.AddressFamily == AddressFamily.InterNetwork)
					{
						localEp = new IPEndPoint(ip, port);
						break;
					}
				}

				if (localEp == null)
				{
					byte[] byteIp = { 192, 168, 0, 1 };
					localEp = new IPEndPoint(new IPAddress(byteIp), port);
				}

				receiver.Bind(localEp);
				receiver.Listen(16);

				// data array always has same length
				byte[] data = new byte[MessageLength];

				while (isRunning)
				{
					// wait for incoming message
					using (Socket handler = receiver.Accept())
					{
						string message = string.Empty;

						do
						{
							int length = handler.Receive(data, MessageLength, SocketFlags.None);
							message += Encoding.ASCII.GetString(data, 0, length);
						}
						while (handler.Available > 0);

						Console.WriteLine(message);

						handler.Close();
						handler.Shutdown(SocketShutdown.Both);
					}
				}

				receiver.Shutdown(SocketShutdown.Both);
				receiver.Close();

				receiver.Dispose();
			}
			catch (SocketException exception)
			{
				Console.WriteLine("> Receiver SocketException: " + exception.Message);
				Console.ReadKey();
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Exception: " + exception.Message);
				Console.ReadKey();
			}
			finally
			{
				if (receiver != null)
				{
					if (receiver.Connected)
					{
						receiver.Shutdown(SocketShutdown.Both);
						receiver.Close();
					}

					receiver.Dispose();
				}
			}
		}

		// sending loop
		private void Send()
		{
			while (isRunning)
			{
				// read message from console
				string message = Console.ReadLine();

				if (message.Length != 0)
				{
					// commands
					if (message[0] == '/')
					{
						if (message[1] == 'q')
						{
							Quit();
						}
						else if (message[1] == 'c')
						{
							ProcessIP(message);
						}
					}
					else
					{
						// format message before sending
						message = name + ": " + message;

						// local print
						// Console.WriteLine(message);

						// send to other peers
						SendMessage(message);
					}
				}
			}
		}

		private void SendMessage(string message)
		{
			try
			{
				byte[] data = Encoding.ASCII.GetBytes(message);

				// send data for each socket
				foreach (IPEndPoint ep in connectedEp)
				{
					using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
					{
						// connect to endpoint
						sender.Connect(ep);

						// convert and send data to it
						sender.Send(data);

						sender.Shutdown(SocketShutdown.Both);
						sender.Close();
					}
				}

			}
			catch (SocketException exception)
			{
				Console.WriteLine("> Sender SocketException: " + exception.Message);
				Console.ReadKey();
			}
			catch (Exception exception)
			{
				Console.WriteLine("> Exception: " + exception.Message);
				Console.ReadKey();
			}
			/*finally
			{
				Free();
			}*/
		}
		#endregion

		#region additional
		private void ReadName()
		{
			while (true)
			{
				Console.Write("> Enter username: ");

				bool success = true;

				string temp = Console.ReadLine();
				name = string.Empty;

				foreach (char c in temp)
				{
					if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
					{
						Console.WriteLine("> Username must contain only symbols: a-z, A-Z, 0-9!");
						success = false;

						break;
					}

					name += c;
				}

				if (!success)
				{
					break;
				}

				if (name.Length > 2)
				{
					break;
				}
				else
				{
					Console.WriteLine("> Username must contain more than 2 symbols!");
				}
			}
		}

		// connect to peer with given ip address
		private void Connect(IPAddress ip)
		{
			IPEndPoint remoteEp = new IPEndPoint(ip, port);

			// make sure that there is no same endpoint
			bool same = false;
			foreach (IPEndPoint ep in connectedEp)
			{
				if (ep.ToString() == remoteEp.ToString())
				{
					same = true;
				}
			}

			if (!same)
			{
				// add to list of all endpoints in current space
				connectedEp.Add(remoteEp);
			}

			// todo: 
			// must receive all IPs from peer we are connecting to,
			// connect to them and add local peer to their lists
		}

		private void ProcessIP(string rawMessage)
		{
			string ipString;
			string[] splitted = rawMessage.Split(' ');

			if (splitted.Length < 2)
			{
				Console.WriteLine("> Not enough arguments!");
				return;
			}

			// assume that after space will be ip
			ipString = splitted[1];

			string temp = string.Empty;
			int dots = 0;

			foreach (char c in ipString)
			{
				if (c >= '0' && c <= '9')
				{
					temp += c;
				}
				else if (c == '.' || c == ',') // c == ' ' ||
				{
					temp += '.';
					dots++;
				}
				else
				{
					Console.WriteLine("> IP must contain only symbols: 0-9, ':', '.'!");
					dots = 0;

					return;
				}
			}

			if (dots != 3)
			{
				Console.WriteLine("> IP must have 4 32-bit numbers!");
				return;
			}

			IPAddress ip;
			if (!IPAddress.TryParse(temp, out ip))
			{
				Console.WriteLine("> Wrong IP!");
				return;
			}

			Console.WriteLine();
			Connect(ip);
		}

		private void Quit()
		{
			while (true)
			{
				Console.Write("> Do you want to quit? Y / N: ");
				string str = Console.ReadLine();

				if (str == "Y" || str == "y")
				{
					Free();
					break;
				}
				else if (str == "N" || str == "n")
				{
					return;
				}
			}
		}

		private void Free()
		{
			isRunning = false;
		}
		#endregion

		#region destructor
		~Peer()
		{
			Free();
		}
		#endregion
	}
}
