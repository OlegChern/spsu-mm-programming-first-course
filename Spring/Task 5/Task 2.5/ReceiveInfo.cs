using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace Chat
{
    public class ReceiveInfo
    {
        public Socket Socket { get; }

        public byte[] Buff { get; set; } 

        public ReceiveInfo(Socket socket)
        {
            Socket = socket;
            Buff = new byte[200];
        }
    }
}
