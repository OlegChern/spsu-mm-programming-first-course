using System;
using System.Collections.Generic;
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
        public bool HasOutcomingConnection => OutcomingConnectionIp != null;
        public bool IsListening { get; private set; }
        public string OutcomingConnectionIp { get; private set; }
        public bool HasConnections => HasOutcomingConnection || IncomingConnectionsCount > 0;

        public Task StartListening()
        {
            if (IsListening)
            {
                throw new InvalidOperationException("Should stop listening before restarting.");
            }

            IsListening = true;
            return Task.Run(() => { });
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

            OutcomingConnectionIp = ip;
            return Task.Run(() => { });
        }

        public void Disconnect()
        {
            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("Should connect before disconnecting.");
            }

            OutcomingConnectionIp = null;
        }

        public Task Send(string message)
        {
            if (!HasOutcomingConnection)
            {
                throw new InvalidOperationException("");
            }

            return Task.Run(() => { });
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
            return Task.Run(() => { });
        }

        public IEnumerable<Task<string>> Receive()
        {
            yield break;
        }
    }
}
