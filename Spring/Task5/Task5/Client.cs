
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;

namespace Task5
{
    sealed class Client : IClient
    {
        public static int DefaultListeningPort => 11000;

        const int BufferSize = 1024;
        const int TimerInterval = 15000;

        public Client()
        {
            IncomingConnections = new List<Socket>();
        }

        public event Action<string> MessageReceived;
        public event Action AutoDisconnected;
        
        #region private members

        Socket listeningSocet;
        Socket outcomingConnection;
        IList<Socket> IncomingConnections { get; }
        Timer timer;
        
        static string ipAddress;
        
        static string IpAddress => ipAddress ?? (ipAddress = Dns.GetHostAddresses(Dns.GetHostName())[0].ToString());

        static string ReceiveMessageFrom(Socket socket)
        {
            // Never receives more than BufferSize
            byte[] array = new byte[BufferSize];

            int bytesRead = socket.Receive(array, SocketFlags.None);

            return bytesRead == 0 ? string.Empty : Encoding.Unicode.GetString(array, 0, bytesRead);
        }

        #endregion private members

        #region interface properties

        public int IncomingConnectionsCount => IncomingConnections.Count;

        public bool HasOutcomingConnection => outcomingConnection != null;

        public bool IsListening => listeningSocet != null;

        public int ListeningPort { get; private set; } = -1;

        public string OutcomingConnectionIp { get; private set; } = "None";

        public bool HasConnections => HasOutcomingConnection || IncomingConnectionsCount > 0;

        #endregion interface properties

        #region interface methods

        public void StartTimer()
        {
            timer = new Timer(obj => Invalidate(), null, TimerInterval, TimerInterval);
        }
        
        public async Task StartListening(int port)
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
            ListeningPort = port;

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

            try
            {
                listeningSocet.Close();
                // Close() calls IDisposable.Dispose() internally
            }
            catch (SocketException e)
            {
                // Ignore
                MessageBox.Show(e.ErrorCode.ToString());
            }
            listeningSocet = null;
            ListeningPort = -1;
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

        public async Task Connect(string ip, int port)
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

        public Task Send(MessageData data)
        {
            return Send(data.Message, data.Socket);
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

            var data = new ArraySegment<byte>(Encoding.Unicode.GetBytes(message));

            if (HasOutcomingConnection && outcomingConnection != ignore)
            {
                await outcomingConnection.SendAsync(data, SocketFlags.None);
            }

            foreach (var socket in IncomingConnections)
            {
                if (socket != ignore)
                {
                    await socket.SendAsync(data, 0);
                }
            }
        }

        public List<MessageData> Receive()
        {
            var result = new List<MessageData>();
            
            if (HasOutcomingConnection)
            {
                string message = ReceiveMessageFrom(outcomingConnection);
                if (!string.IsNullOrEmpty(message))
                {
                    result.Add(new MessageData(message, outcomingConnection));
                }
            }

            result.AddRange(
                from socket in IncomingConnections
                let message = ReceiveMessageFrom(socket)
                where !string.IsNullOrEmpty(message)
                select new MessageData(message, socket)
            );

            return result;
        }

        #endregion interface methods

        public void Dispose()
        {
            timer?.Dispose();
            
            if (IsListening)
            {
                StopListening();
            }

            if (IncomingConnectionsCount != 0)
            {
                TerminateIncomingConnections();
            }

            if (HasOutcomingConnection)
            {
                Disconnect();
            }
        }
        
        async void Invalidate()
        {
            var messagesData = Receive();

            foreach (var data in messagesData)
            {
                if (HasOutcomingConnection && data.Message == IpAddress)
                {
                    Disconnect();
                    AutoDisconnected?.Invoke();
                }
                
                MessageReceived?.Invoke(data.Message);
                
                await Send(data);
            }
        }
    }
}
