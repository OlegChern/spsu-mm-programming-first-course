using System.Net.Sockets;
using System.Threading.Tasks;

namespace Task5
{
    interface IClient
    {
        int IncomingConnectionsCount { get; }

        bool HasOutcomingConnection { get; }

        bool IsListening { get; }

        /// <summary>
        /// Begins accepting incoming connections
        /// </summary>
        Task StartListening();

        /// <summary>
        /// Stops accepting incoming connections
        /// </summary>
        void StopListening();

        void TerminateIncomingConnections();

        Task Connect(string ip);

        void Disconnect();

        /// <summary>
        /// Sends message to all connected devices
        /// </summary>
        /// <param name="message">Text to be sent</param
        Task Send(string message);

        /// <summary>
        /// Sends message to all connected devices but for one
        /// </summary>
        /// <param name="message">Text to be sent</param>
        /// <param name="ignore">Connection with device to be ignored</param>
        Task Send(string message, Socket ignore);
    }
}
