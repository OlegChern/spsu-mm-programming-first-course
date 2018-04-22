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
        private const int MaxRetries = 8;
        #endregion

        #region private fields
        private string name;
        private bool isRunning;

        private Socket receiver;
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

            BindReceiver();

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

                        ProcessReceivedData(message);

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
                List<IPEndPoint> failedConnections = new List<IPEndPoint>();
                int length = data.Length;

                // send data for each socket
                foreach (IPEndPoint ep in connectedEp)
                {
                    using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                    {
                        try
                        {
                            // connect to endpoint
                            sender.Connect(ep);

                            // send data
                            int sendedLength = sender.Send(data);

                            if (length != sendedLength)
                            {
                                // if not all data sended go to catch block
                                throw new Exception();
                            }
                        }
                        catch
                        {
                            // if there is some exception
                            failedConnections.Add(ep);
                            continue;
                        }

                        sender.Shutdown(SocketShutdown.Both);
                        sender.Close();
                    }
                }

                if (failedConnections.Count != 0)
                {
                    ProcessFailedConnections(failedConnections, data);
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
        private void BindReceiver()
        {
            IPEndPoint tempEp = GetLocalEndPoint();

            while (true)
            {
                try
                {
                    tempEp.Port = UserInterface.GetPort();

                    localEp = tempEp;
                    receiver.Bind(localEp);

                    break;
                }
                catch
                {
                    UserInterface.ShowSpecification("This port is already in use!");
                    continue;
                }
            }

            UserInterface.ShowSpecification("Current IPv4: " + localEp.Address.MapToIPv4().ToString());
            UserInterface.ShowSpecification("Current IPv6: " + localEp.Address.MapToIPv6().ToString());
        }

        private IPEndPoint GetLocalEndPoint()
        {
            IPEndPoint ep = null;

            foreach (IPAddress ip in Dns.GetHostEntry(Dns.GetHostName()).AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    ep = new IPEndPoint(ip, 0);
                    break;
                }
            }

            if (ep == null)
            {
                byte[] byteIp = { 192, 168, 0, 1 };
                ep = new IPEndPoint(new IPAddress(byteIp), 0);
            }

            return ep;
        }

        private void ProcessFailedConnections(List<IPEndPoint> list, byte[] data)
        {
            int length = data.Length;

            foreach (IPEndPoint ep in list)
            {
                int retriesCount = 0;

                do
                {
                    using (Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp))
                    {
                        try
                        {
                            // connect to endpoint
                            sender.Connect(ep);

                            // send data
                            int sendedLength = sender.Send(data);

                            if (length != sendedLength)
                            {
                                // if not all data sended go to catch block
                                throw new Exception();
                            }
                        }
                        catch
                        {
                            retriesCount++;
                            continue;
                        }

                        sender.Shutdown(SocketShutdown.Both);
                        sender.Close();
                        break;
                    }
                }
                while (retriesCount < MaxRetries);

                if (retriesCount >= MaxRetries)
                {
                    UserInterface.ShowSpecification("Can't connect to " + ep.ToString() + ". Disconnecting it...");
                    SendDisconnectRequest(ep);
                }
            }
        }

        private void ProcessReceivedData(string message)
        {
            DataType type = DataType.Null;

            if (message != string.Empty)
            {
                // first byte is data type
                type = (DataType)message[0];

                // remove it
                message = message.Remove(0, 1);
            }

            switch (type)
            {
                case DataType.Message:
                    {
                        // just show received message
                        UserInterface.ShowMessage(message);
                        break;
                    }
                case DataType.IPRequest:
                    {
                        // connect to requester's local socket, not to sender socket!
                        IPEndPoint requester;
                        if (GetEndPoint(message, out requester))
                        {
                            Connect(requester, false);

                            // send all current connected endpoints to all peers
                            foreach (IPEndPoint ep in connectedEp)
                            {
                                Send(ep.ToString(), DataType.ConnectRequest);
                            }
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
        }

        // process message to find commands
        // return true if there is any command
        private bool ProcessCommand(string message)
        {
            if (message.Length < 2)
            {
                return false;
            }

            if (message[0] != '/')
            {
                return false;
            }

            if (message.Length > 2 && message[2] != ' ')
            {
                return false;
            }

            switch (message[1])
            {
                case 'c':
                    {
                        // connect to endpoint
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
                        // send disconnect request to all peers
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

        private bool GetEndPoint(string message, out IPEndPoint ep)
        {
            ep = null;

            string[] splitted = message.Split(':');

            IPAddress ip;
            if (splitted.Length < 2)
            {
                return false;
            }
            else if (splitted.Length == 2)
            {
                // ipv4
                if (!IPAddress.TryParse(splitted[0], out ip))
                {
                    return false;
                }
            }
            else
            {
                // ipv6
                if (!IPAddress.TryParse(string.Join(":", splitted, 0, splitted.Length - 2), out ip))
                {
                    return false;
                }
            }

            // last part is port
            int port;
            if (!int.TryParse(splitted[splitted.Length - 1], out port))
            {
                return false;
            }

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
