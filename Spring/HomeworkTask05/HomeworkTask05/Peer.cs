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
        public enum DataType
        {
            Null,
            Message,
            ConnectRequest,
            IPRequest,
            Disconnect
        }
        #endregion

        #region constants
        private const int MessageLength = 256;
		#endregion

		#region private fields
		private string name;
        private bool isRunning;

        Socket receiver;
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
        }

        /// <summary>
        /// Startes sending and receiving
        /// </summary>
        public void Start()
		{
			isRunning = true;

            InitReceiver();
            UserInterface.ShowSpecification("Peer started");

            InitSender();
		}
		#endregion

		#region main methods 
        #region receiving
        private void InitReceiver()
		{
            receiver = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            
            // get local endpoint
            {
                IPEndPoint temp = null;

                foreach (IPAddress ip in Dns.GetHostEntry(Dns.GetHostName()).AddressList)
                {
                    if (ip.AddressFamily == AddressFamily.InterNetwork)
                    {
                        temp = new IPEndPoint(ip, 0);
                        break;
                    }
                }

                if (temp == null)
                {
                    byte[] byteIp = { 192, 168, 0, 1 };
                    temp = new IPEndPoint(new IPAddress(byteIp), 0);
                }

                while (true)
                {
                    try
                    {
                        temp.Port = UserInterface.GetPort();

                        localEp = temp;
                        receiver.Bind(localEp);

                        break;
                    }
                    catch
                    {
                        UserInterface.ShowSpecification("This port is already in use!");
                        continue;
                    }
                }

                UserInterface.ShowSpecification("Current IP and port: " + localEp.ToString());
            }

            // additional thread for receiving messages
            receivingThread = new Thread(new ThreadStart(ReceiveLoop));
			receivingThread.IsBackground = true;
			receivingThread.Start();
		}

        private void ReceiveLoop()
		{
            try
            {
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

                        #region process data type
                        DataType type = DataType.Null;

                        if (message != string.Empty)
                        {
                            type = (DataType)message[0];
                            message = message.Remove(0, 1);
                        }

                        switch (type)
                        {
                            case DataType.Message:
                                {
                                    UserInterface.ShowMessage(message);
                                    break;
                                }
                            case DataType.IPRequest:
                                {
                                    // connect to requester's local socket, not to sender socket!
                                    IPEndPoint requester;
                                    GetEndPoint(message, out requester);
                                    Connect(requester, false);

                                    // send all current connected endpoints to all peers
                                    foreach (IPEndPoint ep in connectedEp)
                                    {
                                        Send(ep.ToString(), DataType.ConnectRequest);
                                    }

                                    break;
                                }
                            case DataType.ConnectRequest:
                                {
                                    // connect to received endpoint
                                    IPEndPoint ep;
                                    if (GetEndPoint(message, out ep))
                                    {
                                        Connect(ep, false);
                                    }

                                    break;
                                }
                            case DataType.Disconnect:
                                {
                                    // get received endpoint and then disconnect it
                                    IPEndPoint ep;
                                    if (GetEndPoint(message, out ep))
                                    {
                                        Disconnect(ep);
                                    }

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

                if (message.Length == 0)
                {
                    continue;
                }

                if (!ProcessCommand(message))
                {
                    // format message before sending
                    message = DateTime.Now.ToString("[HH:mm:ss]") + name + ": " + message;

                    // send to other peers
                    Send(message, DataType.Message);
                }
            }
        }

        // send message to all
        private void Send(string message, DataType type)
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

        private void Send(byte[] data)
        {
            try
            {
                // create temp list because the original one is changed in loop
                List<IPEndPoint> tempList = new List<IPEndPoint>(connectedEp);
                int length = data.Length;

                // send data for each socket
                foreach (IPEndPoint ep in tempList)
                {
                    using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                    {
                        try
                        {
                            // connect to endpoint
                            sender.Connect(ep);
                        }
                        catch
                        {
                            UserInterface.ShowSpecification("Can't connect to " + ep.ToString() + ". Disconnecting it...");
                            SendDisconnectRequest(ep);

                            continue;
                        }

                        int sendedLength = sender.Send(data);

                        if (length != sendedLength)
                        {
                            sender.Send(data);
                        }

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
            Send(localEp.ToString(), DataType.IPRequest);
        }

        private void SendDisconnectRequest(IPEndPoint ep)
        {
            if (ep != localEp)
            {
                Disconnect(ep);
            }

            Send(ep.ToString(), DataType.Disconnect);
        }
        #endregion

        private void Connect(IPEndPoint ep, bool showMessage)
        {
            // make sure that there is no same endpoint
            if (connectedEp.Contains(ep))
            {
                if (showMessage)
                {
                    UserInterface.ShowSpecification("Already connected to " + ep.ToString());
                }
            }
            else if (ep.ToString() == localEp.ToString())
            {
                if (showMessage)
                {
                    UserInterface.ShowSpecification("Can't connect to same IP and port");
                }
            }
            else
            {
                // check existence
                using (Socket check = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                {
                    try
                    {
                        // connect to endpoint
                        check.Connect(ep);
                    }
                    catch
                    {
                        UserInterface.ShowSpecification("Can't connect to " + ep.ToString());
                        return;
                    }
                }

                // add to list of all endpoints in current space
                connectedEp.Add(ep);
                SendIPRequest();

                if (showMessage)
                {
                    UserInterface.ShowSpecification("Connected to " + ep.ToString());
                    Send(name + " connected.", DataType.Message);
                }
            }
        }

        private void Disconnect(IPEndPoint ep)
        {
            if (connectedEp.Contains(ep) && ep.ToString() != localEp.ToString())
            {
                connectedEp.Remove(ep);
                UserInterface.ShowSpecification(ep.ToString() + " disconnected");
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
                                if (UserInterface.GetEndPoint(message, out ep))
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
                                SendDisconnectRequest(localEp);
                                connectedEp.Clear();

                                UserInterface.ShowSpecification("Disconnected");
                                break;
                            }
                        case 'q':
                            {
                                Exit();
                                break;
                            }
                    }

                    return true;
                }
            }

            return false;
        }

        public static bool GetEndPoint(string message, out IPEndPoint ep)
        {
            ep = null;

            string[] ipSplitted = message.Split('.', ':');

            if (ipSplitted.Length < 5)
            {
                return false;
            }

            // read ip
            byte[] ipBytes = new byte[4];

            for (int i = 0; i < 4; i++)
            {
                ipBytes[i] = byte.Parse(ipSplitted[i]);
            }

            IPAddress ip = new IPAddress(ipBytes);
            int port = int.Parse(ipSplitted[4]);

            ep = new IPEndPoint(ip, port);
            return true;
        }

        private void ShowAllConnections()
        {
            if (connectedEp.Count == 0)
            {
                UserInterface.ShowSpecification("Not connected");
                return;
            }

            UserInterface.ShowSpecification("Connected to:");
            foreach (IPEndPoint ep in connectedEp)
            {
                UserInterface.ShowMessage("  " + ep.ToString());
            }
        }

        private void Exit()
        {
            if (UserInterface.RequestExit())
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
            SendDisconnectRequest(localEp);
            isRunning = false;
            connectedEp.Clear();
        }
        #endregion
    }
}
