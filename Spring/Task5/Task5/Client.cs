using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Task5.Events;

// TODO: chat crashes after an attempt to connect to itself, fix

namespace Task5
{
    sealed class Client : AbstractClient
    {
        const int BufferSize = 1024;

        public Client()
        {
            incomingConnections = new List<Socket>();
        }

        public override event EventHandler<MessageReceivedEventArgs> MessageReceived;
        public override event EventHandler<ConnectionsCountChangedEventArgs> ConnectionsCountChanged;
        public override event EventHandler ListeningStateChanged;

        #region private members

        Socket listeningSocet;
        Socket outcomingConnection;
        readonly IList<Socket> incomingConnections;

        string IpAddressMessage => outcomingConnection?.LocalEndPoint?.ToString();

        async void StartReceivingMessages(Socket socket)
        {
            byte[] array = new byte[BufferSize];
            var segment = new ArraySegment<byte>(array);

            while (true)
            {
                if (!socket.Connected)
                {
                    StopHandling(socket);
                    return;
                }

                int bytesRead;
                try
                {
                    bytesRead = await socket.ReceiveAsync(segment, SocketFlags.None);
                }
                catch (Exception e)
                {
                    MessageBox.Show($"One of devices must have been disconnected:{Environment.NewLine}{e}",
                        "Error reading data");
                    StopHandling(socket);
                    return;
                }

                string message = Encoding.Unicode.GetString(array, 0, bytesRead);

                if (string.IsNullOrWhiteSpace(message))
                {
                    StopHandling(socket);
                    MessageBox.Show("One of devices must have been disconnected", "Error: empty string received");
                    return;
                }

                if (message == IpAddressMessage)
                {
                    Disconnect();
                    MessageBox.Show("Disconnected due to loops in network", "Connection terminated");
                    ConnectionsCountChanged?.Invoke(this, new ConnectionsCountChangedEventArgs(ConnectionsCount));
                    return;
                }

                MessageReceived?.Invoke(this, new MessageReceivedEventArgs(message));
                await Send(message, socket);
            }
        }

        void StopHandling(Socket socket)
        {
            if (socket == outcomingConnection)
            {
                Disconnect();
                return;
            }

            if (incomingConnections.Remove(socket))
            {
                ConnectionsCountChanged?.Invoke(this, new ConnectionsCountChangedEventArgs(ConnectionsCount));
                return;
            }
            
            throw new InvalidOperationException("StopHandling() was given a socket that doesn't belong to client");
        }

        #endregion private members

        public override int IncomingConnectionsCount => incomingConnections.Count;

        public override int ListeningPort => (listeningSocet?.LocalEndPoint as IPEndPoint)?.Port ?? -1;

        public override string OutcomingConnectionIp =>
            (outcomingConnection?.LocalEndPoint as IPEndPoint)?.Address?.ToString();

        public override bool HasConnections => HasOutcomingConnection || IncomingConnectionsCount > 0;

        #region public methods

        public override void StartListening(int port)
        {
            if (IsListening)
            {
                throw new InvalidOperationException("Should stop listening before restarting.");
            }

            // Establish the local endpoint for the socket.    
            var ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            var ipAddress = ipHostInfo.AddressList[0];
            var localEndPoint = new IPEndPoint(ipAddress, port);

            // Create a TCP/IP socket.  
            var listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // Bind the socket to the local endpoint
            listener.Bind(localEndPoint);

            listener.Listen(100);

            // I'm not sure about thread-safety of this assignment.
            // Let's just hope code above executes quickly enough to prevent problems
            listeningSocet = listener;

            ListeningStateChanged?.Invoke(this, EventArgs.Empty);

            Handle();
        }

        async void Handle()
        {
            // Listen for connections
            while (true)
            {
                if (!IsListening)
                {
                    return;
                }

                Socket handler;
                try
                {
                    // this operation is canceled when socket gets disposed
                    handler = await listeningSocet.AcceptAsync();
                    StartReceivingMessages(handler);
                }
                catch (SocketException)
                {
                    return;
                }

                incomingConnections.Add(handler);
                ConnectionsCountChanged?.Invoke(this, new ConnectionsCountChangedEventArgs(ConnectionsCount));
            }
        }

        public override void StopListening()
        {
            if (!IsListening)
            {
                throw new InvalidOperationException("Should start listening before stopping.");
            }

            try
            {
                listeningSocet.Close();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), "Error");
            }

            listeningSocet = null;
            ListeningStateChanged?.Invoke(this, EventArgs.Empty);
        }

        public override void TerminateIncomingConnections()
        {
            // TODO: do I really need to lock?
            // Probably not, but I'm afraid to modify this old code
            lock (incomingConnections)
            {
                foreach (var socket in incomingConnections)
                {
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                }

                incomingConnections.Clear();
            }

            ConnectionsCountChanged?.Invoke(this, new ConnectionsCountChangedEventArgs(ConnectionsCount));
        }

        public override async Task Connect(string ip, int port)
        {
            if (HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should disconnect before estabinishing another connection.");
            }

            // Establish the remote endpoint for the socket.    
            var ipHostInfo = Dns.GetHostEntry(ip);
            var ipAddress = ipHostInfo.AddressList[0];
            var remoteEp = new IPEndPoint(ipAddress, port);

            // Create a TCP/IP socket.  
            var client = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // Connect to the remote endpoint. 
            await client.ConnectAsync(remoteEp);

            outcomingConnection = client;

            // This action should terminate current connection if loops are present
            await Send(IpAddressMessage);

            ConnectionsCountChanged?.Invoke(this, new ConnectionsCountChangedEventArgs(ConnectionsCount));

            StartReceivingMessages(client);
        }

        public override void Disconnect()
        {
            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should connect before disconnecting.");
            }

            outcomingConnection.Shutdown(SocketShutdown.Both);
            outcomingConnection.Close();
            outcomingConnection = null;

            ConnectionsCountChanged?.Invoke(this, new ConnectionsCountChangedEventArgs(ConnectionsCount));
        }

        public override Task Send(string message)
        {
            return Send(message, null);
        }

        public override Task Send(MessageData data)
        {
            return Send(data.Message, data.Socket);
        }

        public override async Task Send(string message, Socket ignore)
        {
            if (string.IsNullOrWhiteSpace(message))
            {
                throw new ArgumentException(nameof(message));
            }

            if (!HasConnections)
            {
                throw new InvalidOperationException("Should get connections before sending messages.");
            }

            var data = new ArraySegment<byte>(Encoding.Unicode.GetBytes(message));

            if (HasOutcomingConnection && outcomingConnection != ignore)
            {
                await outcomingConnection.SendAsync(data, SocketFlags.None);
            }

            foreach (var socket in incomingConnections)
            {
                if (socket != ignore)
                {
                    await socket.SendAsync(data, 0);
                }
            }
        }

        #endregion public methods
    }
}
