﻿using System.Collections.Generic;
using System.Net.Sockets;
using System.Threading.Tasks;

namespace Task5
{
    interface IClient
    {
        int IncomingConnectionsCount { get; }

        bool HasOutcomingConnection { get; }
        
        string OutcomingConnectionIp { get; }

        bool IsListening { get; }
        
        bool HasConnections { get; }

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
        /// <param name="message">Text to be sent</param>
        Task Send(string message);

        /// <summary>
        /// Sends message to all connected devices but for one
        /// </summary>
        /// <param name="message">Text to be sent</param>
        /// <param name="ignore">Connection with device to be ignored</param>
        Task Send(string message, Socket ignore);

        /// <summary>
        /// Receives messages from all connected devices
        /// </summary>
        /// <returns>
        /// List of tasks returning messages
        /// </returns>
        IEnumerable<Task<string>> Receive();
    }
}
