using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization.Formatters.Binary;

namespace Chat
{
    public class ChatClient
    {
        public string Name { get; }

        public bool IsConnect { get; private set; }

        public bool IsListen { get; private set; }

        public ChatWindow Chat { get; }

        public IPAddress MyIP { get; private set; }

        public int MyPort { get; }

        public List<IPEndPoint> Points { get; private set; }

        public List<IPEndPoint> NewPoints { get; private set; }

        public IPEndPoint IPEndPoint { get; private set; }

        public Socket SocketServer { get; private set; }

        public List<Socket> ListenedSockets { get; private set; }

        public List<Socket> ConnectedSockets { get; private set; }

        public bool CanConnect { get; private set; }

        public ChatClient(string name, int port, ChatWindow chat)
        {
            CanConnect = true;
            MyPort = port;
            Name = name;
            Chat = chat;
            SocketServer = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            ConnectedSockets = new List<Socket>();
            ListenedSockets = new List<Socket>();
            MyIP = Chat.IP;
            IPEndPoint = new IPEndPoint(MyIP, MyPort);
            Points = new List<IPEndPoint>
            {
                IPEndPoint
            };
            NewPoints = new List<IPEndPoint>();
            StartListen();
        }

        public void Connect(IPEndPoint point)
        {
            try
            {
                var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                socket.Connect(point);
                Points.Add(point);
                CanConnect = true;
                ConnectedSockets.Add(socket);
                ExchangeDataClient(socket);
                var recInfo = new ReceiveInfo(socket);
                socket.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receive), recInfo);
                if (!IsConnect)
                {
                    Chat.ConnectChat();
                }
                IsConnect = true;
                Chat.ChangeListAdress();
                if (NewPoints.Count != 0)
                {
                    var pointClient = NewPoints[NewPoints.Count - 1];
                    NewPoints.Remove(pointClient);
                    while (!CanConnect)
                    {
                        Thread.Sleep(200);
                    }
                    if (!Points.Contains(pointClient))
                    {
                            CanConnect = false;
                            Connect(pointClient);
                    }
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        private void ExchangeDataClient(Socket socket)
        {
            try
            {
                var netStream = new NetworkStream(socket, true);
                var formatter = new BinaryFormatter();
                var points = (List<IPEndPoint>)formatter.Deserialize(netStream);
                formatter.Serialize(netStream, Points);
                foreach (var e in points)
                {
                    if ((!Points.Contains(e)) && (!NewPoints.Contains(e)))
                    {
                        NewPoints.Add(e);
                    }
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public void StartListen()
        {
            try
            {
                SocketServer.Bind(IPEndPoint);
                SocketServer.Listen(16);
                SocketServer.BeginAccept(new AsyncCallback(NewClient), null);
                IsListen = true;
            }
            catch (Exception ex)
            {
                IsListen = false;
                Chat.PrintException(ex.Message);
            }
        }

        private void NewClient(IAsyncResult async)
        {
            try
            {
                if (IsListen)
                {
                    var socket = SocketServer.EndAccept(async);
                    ListenedSockets.Add(socket);
                    ExchangeDataServer(socket);
                    StartReceive(socket);
                    if (!IsConnect)
                    {
                        Chat.ConnectChat();
                    }
                    IsConnect = true;
                    SocketServer.BeginAccept(new AsyncCallback(NewClient), null);
                    if (NewPoints.Count != 0)
                    {
                        var pointClient = NewPoints[NewPoints.Count - 1];
                        NewPoints.Remove(pointClient);
                        while (!CanConnect)
                        {
                            Thread.Sleep(200);
                        }
                        if (!Points.Contains(pointClient))
                        {
                            CanConnect = false;
                            Connect(pointClient);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        private void ExchangeDataServer(Socket socket)
        {
            try
            {
                var netStream = new NetworkStream(socket, true);
                var formatter = new BinaryFormatter();
                formatter.Serialize(netStream, Points);
                var points = (List<IPEndPoint>)formatter.Deserialize(netStream);
                foreach (var e in points)
                {
                    if (!Points.Contains(e))
                    {
                        NewPoints.Add(e);
                        Chat.PrintMessage("Подключился пользователь " + e.ToString() + "\n");
                    }
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public void StartReceive(Socket socket)
        {
            try
            {
                var recInfo = new ReceiveInfo(socket);
                socket.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receive), recInfo);
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public void Receive(IAsyncResult async)
        {
            var recInfo = (ReceiveInfo)async.AsyncState;
            try
            {
                if (IsConnect)
                {
                    var read = recInfo.Socket.EndReceive(async);
                    if (read > 0)
                    {
                        var str = Encoding.Unicode.GetString(recInfo.Buff, 0, read);
                        Chat.PrintMessage(str);
                    }
                    recInfo.Socket.BeginReceive(recInfo.Buff, 0, recInfo.Buff.Length, SocketFlags.None, new AsyncCallback(Receive), recInfo);
                }
            }
            catch (SocketException ex)
            {
                if (ex.ErrorCode == 10054)
                {
                    if (ConnectedSockets.Contains(recInfo.Socket))
                    {
                        var index = ConnectedSockets.IndexOf(recInfo.Socket);
                        ConnectedSockets.RemoveAt(index);
                        Chat.PrintMessage("Отключился пользователь " + Points[index + 1] + "\n");
                        Points.RemoveAt(index + 1);
                        Chat.ChangeListAdress();
                    }
                    else
                    {
                        var index = ListenedSockets.IndexOf(recInfo.Socket);
                        ListenedSockets.RemoveAt(index);
                    }
                    recInfo.Socket.Close();          
                    if ((ConnectedSockets.Count == 0) && (ListenedSockets.Count == 0))
                    {
                        IsConnect = false;
                        Chat.DisconnectChat();
                    }
                }
                else
                {
                    Chat.PrintException(ex.Message);
                }
            }
        }

        public void Send(string str)
        {
            try
            {
                if (IsConnect)
                {
                    var data = Encoding.Unicode.GetBytes(str);

                    foreach (var e in ConnectedSockets)
                    {
                        e.Send(data);
                    }

                    Chat.PrintMessage(str);
                }
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public void Disconnect()
        {
            try
            {
                IsConnect = false;
                foreach (var e in ListenedSockets)
                {
                    e.Close();
                }
                foreach (var e in ConnectedSockets)
                {
                    e.Close();
                }
                ConnectedSockets.Clear();
                Points.Clear();
                Points.Add(IPEndPoint);
                Chat.ChangeListAdress();
            }
            catch (Exception ex)
            {
                Chat.PrintException(ex.Message);
            }
        }

        public void Exit()
        {
            Disconnect();
            IsListen = false;
            SocketServer.Close();
        }
    }
}
