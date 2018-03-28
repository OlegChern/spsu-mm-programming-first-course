using System;
using System.Collections.Generic;
using System.Text;

using System.Threading;
using System.Net;
using System.Net.Sockets;

namespace Chat
{
	class Peer
	{
        #region enums
        public enum MessageType
        {
            Null = 0,
            Message = 1,
            IP = 2,
            IPRequest = 3,
            Disconnect = 4
        }
        #endregion

        #region constants
        private const int MessageLength = 256;
		#endregion

		#region private fields
		private string name;
        private int port;

        private bool isRunning;

		private Thread receivingThread;

        private IPEndPoint localEp = null;
        private List<IPEndPoint> connectedEp = new List<IPEndPoint>();
		#endregion

		#region public methods
		/// <summary>
		/// Creates new peer
		/// </summary>
		public Peer()
		{
            name = UserInterface.GetName();
            port = UserInterface.GetPort();
        }

        /// <summary>
        /// Startes sending and receiving
        /// </summary>
        public void Start()
		{
			isRunning = true;

            UserInterface.ShowMessage("> Peer started");

            InitReceiver();
            InitSender();
		}
		#endregion

		#region main methods 
        #region receiving
        private void InitReceiver()
		{
			// additional thread for receiving messages
			receivingThread = new Thread(new ThreadStart(ReceiveLoop));
			receivingThread.IsBackground = true;
			receivingThread.Start();
		}

        private void ReceiveLoop()
		{
			Socket receiver = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                // get local end point
                foreach (IPAddress ip in Dns.GetHostEntry(Dns.GetHostName()).AddressList)
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

                UserInterface.ShowMessage("> Current IP and port: " + localEp.ToString());

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

                        #region process message type
                        MessageType type = MessageType.Null;

                        if (message != string.Empty)
                        {
                            type = (MessageType)message[0];
                            message = message.Remove(0, 1);
                        }

                        switch (type)
                        {
                            case MessageType.Message:
                                {
                                    UserInterface.ShowMessage(message);
                                    break;
                                }
                            case MessageType.IPRequest:
                                {
                                    // connect to requester's local socket, not to sender socket!
                                    IPEndPoint requester;
                                    UserInterface.GetEndPoint(false, message, out requester);
                                    Connect(requester, false);

                                    // send all current connected endpoints to all peers
                                    foreach (IPEndPoint ep in connectedEp)
                                    {
                                        Send(ep.ToString(), MessageType.IP);
                                    }

                                    break;
                                }
                            case MessageType.IP:
                                {
                                    IPEndPoint ep;
                                    if (UserInterface.GetEndPoint(false, message, out ep))
                                    {
                                        Connect(ep, false);
                                    }

                                    break;
                                }
                            case MessageType.Disconnect:
                                {
                                    // get requester's endpoint and then disconnect it
                                    IPEndPoint requester;
                                    UserInterface.GetEndPoint(false, message, out requester);
                                    Disconnect(requester);

                                    break;
                                }
                        }
                        #endregion

                        handler.Shutdown(SocketShutdown.Both);
						handler.Close();
					}
				}

				receiver.Shutdown(SocketShutdown.Both);
				receiver.Close();

				receiver.Dispose();
			}
			catch (SocketException exception)
			{
                UserInterface.ShowException(exception, "Receiver");
			}
			catch (Exception exception)
			{
                UserInterface.ShowException(exception);
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
        #endregion

        #region sending
        private void InitSender()
        {
            SendLoop();
        }

        private void SendLoop()
		{
			while (isRunning)
			{
                string message = UserInterface.GetMessage();

                if (!ProcessCommand(message))
                {
                    // format message before sending
                    message = DateTime.Now.ToString("[HH:mm:ss]") + name + ": " + message;

                    // send to other peers
                    Send(message, MessageType.Message);
                }
            }
        }

        // send message to all
        private void Send(string message, MessageType type)
		{
			try
			{
                // using first byte as message type
                byte[] temp = Encoding.ASCII.GetBytes(message);
                int tempLength = temp.Length;

                byte[] data = new byte[tempLength + 1];

                data[0] = (byte)type;
                Array.Copy(temp, 0, data, 1, tempLength);

                Send(data);
			}
            catch (Exception exception)
			{
                UserInterface.ShowException(exception);
            }
        }

        // send message to exact ip
        private void Send(IPEndPoint ep, string message, MessageType type)
        {
            try
            {
                // using first byte as message type
                byte[] temp = Encoding.ASCII.GetBytes(message);
                int tempLength = temp.Length;

                byte[] data = new byte[tempLength + 1];

                data[0] = (byte)type;
                Array.Copy(temp, 0, data, 1, tempLength);

                using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    // connect to endpoint
                    sender.Connect(ep);

                    sender.Send(data);

                    sender.Shutdown(SocketShutdown.Both);
                    sender.Close();
                }
            }
            catch (SocketException exception)
            {
                UserInterface.ShowException(exception, "Sender");
            }
            catch (Exception exception)
            {
                UserInterface.ShowException(exception);
            }
        }

        private void Send(byte[] data)
        {
            try
            {
                // send data for each socket
                foreach (IPEndPoint ep in connectedEp)
                {
                    using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                    {
                        // connect to endpoint
                        sender.Connect(ep);

                        sender.Send(data);

                        sender.Shutdown(SocketShutdown.Both);
                        sender.Close();
                    }
                }

            }
            catch (SocketException exception)
            {
                UserInterface.ShowException(exception, "Sender");
            }
            catch (Exception exception)
            {
                UserInterface.ShowException(exception);
            }
        }

        private void SendIPRequest()
        {
            Send(localEp.ToString(), MessageType.IPRequest);
        }

        private void SendDisconnectRequest()
        {
            Send(localEp.ToString(), MessageType.Disconnect);
        }
        #endregion

        private void Connect(IPEndPoint ep, bool showMesage)
        {
            // make sure that there is no same endpoint
            if (connectedEp.Contains(ep))
            {
                if (showMesage)
                {
                    UserInterface.ShowMessage("> Already connected to " + ep.ToString());
                }
            }
            else if (ep.ToString() == localEp.ToString())
            {
                if (showMesage)
                {
                    UserInterface.ShowMessage("> Can't connect to same IP and port");
                }
            }
            else
            {
                // add to list of all endpoints in current space
                connectedEp.Add(ep);
                SendIPRequest();

                if (showMesage)
                {
                    UserInterface.ShowMessage("> Connected to " + ep.ToString());
                    Send(name + " connected.", MessageType.Message);
                }
            }
        }

        private void Disconnect(IPEndPoint ep)
        {
            if (connectedEp.Contains(ep) && ep.ToString() != localEp.ToString())
            {
                connectedEp.Remove(ep);
                UserInterface.ShowMessage("> " + ep.ToString() + " disconnected");
            }
        }
        #endregion

        #region additional methods
        // process message to find commands
        // return true if there is any command
        private bool ProcessCommand(string message)
        {
            if (message.Length > 1)
            {
                if (message[0] == '/')
                {
                    switch(message[1])
                    {
                        case 'c':
                            {
                                IPEndPoint ep;
                                if (UserInterface.GetEndPoint(true, message, out ep))
                                {
                                    Connect(ep, true);
                                }

                                break;
                            }
                        case 's':
                            {
                                ShowAllConnections();
                                break;
                            }
                        case 'd':
                            {
                                SendDisconnectRequest();
                                connectedEp.Clear();

                                UserInterface.ShowMessage("> Disconnected");
                                break;
                            }
                        case 'q':
                            {
                                Quit();
                                break;
                            }
                    }

                    return true;
                }
            }

            return false;
        }

        private void ShowAllConnections()
        {
            if (connectedEp.Count == 0)
            {
                UserInterface.ShowMessage("> Not connected");
                return;
            }

            UserInterface.ShowMessage("> Connected to:");
            foreach (IPEndPoint ep in connectedEp)
            {
                UserInterface.ShowMessage("  " + ep.ToString());
            }
        }

        private void Quit()
        {
            if (UserInterface.ToQuit())
            {
                Free();
            }
        }
        #endregion

        #region freeing memory
        ~Peer()
		{
			Free();
		}

        private void Free()
        {
            SendDisconnectRequest();
            isRunning = false;
            connectedEp.Clear();
        }
        #endregion
    }
}
