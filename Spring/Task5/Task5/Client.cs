using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Task5
{
    sealed class Client : IClient
    {
        public const int ListeningPort = 11000;

        public const int BufferSize = 1024;

        public Client()
        {
            IncomingConnections = new List<Socket>();
        }

        #region private members

        Socket listeningSocet;
        Socket outcomingConnection;
        IList<Socket> IncomingConnections { get; }

        static async Task<string> ReceiveMessageFrom(Socket socket)
        {
            // Never receives more than BufferSize
            byte[] array = new byte[BufferSize];
            var segment = new ArraySegment<byte>(array);

            int bytesRead = await socket.ReceiveAsync(segment, SocketFlags.None);

            return Encoding.Unicode.GetString(array, 0, bytesRead);
        }

        #endregion private members

        #region interface properties

        public int IncomingConnectionsCount => IncomingConnections.Count;

        public bool HasOutcomingConnection => outcomingConnection != null;

        public bool IsListening => listeningSocet != null;

        public string OutcomingConnectionIp { get; private set; } = "None";

        public bool HasConnections => HasOutcomingConnection || IncomingConnectionsCount > 0;

        #endregion interface properties

        #region interface methods

        // TODO: handle all kinds of exceptions here

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

                IncomingConnections.Add(handler);
                MainWindow.Instance.ConnectiosScreen.Text =
                    $"Connections: {IncomingConnectionsCount + (HasOutcomingConnection ? 1 : 0)}";
                if (SettingsWindow.HasInstance)
                {
                    SettingsWindow.Instance.IncomingConnectionsScreen.Text =
                        $"Incoming connections: {IncomingConnectionsCount}";
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
            lock (IncomingConnections)
            {
                foreach (var socket in IncomingConnections)
                {
                    socket.Shutdown(SocketShutdown.Both);
                    socket.Close();
                }

                IncomingConnections.Clear();
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

            OutcomingConnectionIp = ip;
            outcomingConnection = client;

            // This action should terminate current connection if loops are present
            await Send(OutcomingConnectionIp);
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
            OutcomingConnectionIp = "None";
        }

        public Task Send(string message)
        {
            return Send(message, null);
        }

        public async Task Send(string message, Socket ignore)
        {
            if (string.IsNullOrWhiteSpace(message))
            {
                throw new ArgumentException(nameof(message));
            }

            if (!HasConnections)
            {
                throw new InvalidOperationException("Should get connections before sending messages.");
            }

            var data = new ArraySegment<byte>(Encoding.UTF8.GetBytes(message), 0, BufferSize);

            if (HasOutcomingConnection && outcomingConnection != ignore)
            {
                await outcomingConnection.SendAsync(data, 0);
            }

            foreach (var socket in IncomingConnections)
            {
                if (socket != ignore)
                {
                    await socket.SendAsync(data, 0);
                }
            }
        }

        public IEnumerable<Task<string>> Receive()
        {
            if (!HasConnections)
            {
                yield break;
            }

            if (HasOutcomingConnection)
            {
                yield return ReceiveMessageFrom(outcomingConnection);
            }

            foreach (var socket in IncomingConnections)
            {
                yield return ReceiveMessageFrom(socket);
            }
        }

        #endregion interface methods
    }
}
