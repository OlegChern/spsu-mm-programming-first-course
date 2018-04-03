using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Task5
{
    sealed class Client : IClient
    {
        public const int ListeningPort = 11000;

        public Client()
        {
            incomingConnections = new List<Socket>();
        }

        #region private fields

        volatile Socket listeningSocet;
        volatile IList<Socket> incomingConnections;
        volatile Socket outcomingConnection;

        #endregion

        #region interface properties

        public int IncomingConnectionsCount
        {
            get
            {
                lock (incomingConnections)
                {
                    return incomingConnections.Count;
                }
            }
        }

        public bool HasOutcomingConnection => outcomingConnection != null;

        public bool IsListening => listeningSocet != null;

        #endregion interface properties

        #region interface methods

        // TODO: handle all kinds of exceptions here
        // TODO: do actual callback handling, not just accept inputs

        public async Task StartListening()
        {
            if (IsListening)
            {
                throw new InvalidOperationException("Should stop listening before restarting.");
            }

            // Establish the local endpoint for the socket.    
            var ipHostInfo = Dns.GetHostEntry(Dns.GetHostName());
            var ipAddress = ipHostInfo.AddressList[0];
            var localEndPoint = new IPEndPoint(ipAddress, ListeningPort);

            // Create a TCP/IP socket.  
            var listener = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // Bind the socket to the local endpoint
            listener.Bind(localEndPoint);
            listener.Listen(100);

            // I'm not sure about thread-safety of this assignment.
            // Let's just hope code above executes quickly enough to prevent problems
            listeningSocet = listener;

            // Listen for connections
            while (true)
            {
                if (!IsListening)
                {
                    return;
                }

                Socket handler;
                // As far as I understand, this operation is canceled when socket gets disposed
                try
                {
                    handler = await listeningSocet.AcceptAsync();
                }
                catch (ObjectDisposedException)
                {
                    return;
                }

                // SocketException is not handled
                lock (incomingConnections)
                {
                    incomingConnections.Add(handler);
                }
            }
        }

        public void StopListening()
        {
            if (!IsListening)
            {
                throw new InvalidOperationException("Should start listening before stopping.");
            }

            listeningSocet.Shutdown(SocketShutdown.Both);
            listeningSocet.Close();
            // Close() calls IDisposable.Dispose() internally
            listeningSocet = null;
        }

        public void TerminateIncomingConnections()
        {
            lock (incomingConnections)
            {
                foreach (var socket in incomingConnections)
                {
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                }

                incomingConnections.Clear();
            }
        }

        public async Task Connect(string ip)
        {
            if (HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should disconnect before estabinishing another connection.");
            }

            // Establish the remote endpoint for the socket.    
            var ipHostInfo = Dns.GetHostEntry(ip);
            var ipAddress = ipHostInfo.AddressList[0];
            var remoteEp = new IPEndPoint(ipAddress, ListeningPort);

            // Create a TCP/IP socket.  
            var client = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

            // Connect to the remote endpoint. 
            await client.ConnectAsync(remoteEp);

            outcomingConnection = client;
        }

        public void Disconnect()
        {
            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should connect before disconnecting.");
            }

            outcomingConnection.Shutdown(SocketShutdown.Both);
            outcomingConnection.Close();
            outcomingConnection = null;
        }

        // TODO: assert that no loops appeared in network
        public async Task Send(string message)
        {
            if (string.IsNullOrWhiteSpace(message))
            {
                throw new ArgumentException(nameof(message));
            }

            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should connect before sending messages.");
            }

            throw new NotImplementedException();
        }

        public async Task Send(string message, Socket ignore)
        {
            throw new NotImplementedException();
        }

        #endregion interface methods
    }
}
