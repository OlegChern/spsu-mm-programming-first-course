using System;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Task5
{
    /// <summary>
    /// Class exists merely for debugging purposes
    /// </summary>
    public class FakeClient : IClient
    {
        public int IncomingConnectionsCount { get; private set; }
        public bool HasOutcomingConnection { get; private set; }
        public bool IsListening { get; private set; }

        public Task StartListening()
        {
            if (IsListening)
            {
                throw new InvalidOperationException("Should stop listening before restarting.");
            }

            IsListening = true;
            return null;
        }

        public void StopListening()
        {
            if (!IsListening)
            {
                throw new InvalidOperationException("Should start listening before stopping.");
            }

            IsListening = false;
        }

        public void TerminateIncomingConnections()
        {
            IncomingConnectionsCount = 0;
        }

        public Task Connect(string ip)
        {
            if (HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should disconnect before estabinishing another connection.");
            }

            HasOutcomingConnection = true;
            return null;
        }

        public void Disconnect()
        {
            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should connect before disconnecting.");
            }

            HasOutcomingConnection = false;
        }

        public Task Send(string message)
        {
            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("");
            }

            return null;
        }

        public Task Send(string message, Socket ignore)
        {
            if (string.IsNullOrWhiteSpace(message))
            {
                throw new ArgumentException(nameof(message));
            }

            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should connect before sending messages.");
            }

            // Now ok, I sent it
            return null;
        }
    }
}
