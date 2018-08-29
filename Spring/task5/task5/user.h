#pragma once
class user
{
private:
	static string exitCommand;
	static string ip;
	static string incorrectAdress;
	static string usedAdress;
	map <int, SOCKET>::iterator it;

	static string recieveClient(SOCKET socket);

	static string recieveClient(LPVOID client_socket);

	static int systemCommand(string s);

	/// <summary>
	/// показывает сообщение об ошибке
	/// Деиницилизация библиотеки Winsock 
	/// </summary>
	static void ShowError();

	static string convert(int a);

	/// <summary>
	/// Отделить ip и port
	/// </summary>
	/// <returns></returns>
	static pair<string, string> parser(string s);

	/// <summary>
	/// печатает сообщения  в консоли
	/// </summary>
	/// <param name="message"></param>
	static void LogMessage(string message);

	/// <summary>
	/// Корректный выход
	/// </summary>
	static void Exit(SOCKET socket);

public:
	static int port;
	static bool exitFlag;
	static string name;
	static map <int, SOCKET> clients;
	static int lastPort;

	/// <summary>
	/// отправка сообщения
	/// </summary>
	/// <param name="socket"></param>
	/// <param name="message"></param>
	static void Send(SOCKET socket, string message);

	/// <summary>
	/// Создает сокет
	/// </summary>
	/// <returns></returns>
	static SOCKET InitSocket();

	static DWORD WINAPI GetNewMessage(LPVOID clientSocket)
	{
		string message = "";
		map <int, SOCKET>::iterator it;
		while ((message = recieveClient(clientSocket)) != "") {
			int check = systemCommand(message);
			switch (check)
			{
			case -1:
			{
				printf("%s\n", message.c_str());
				break;
			}
			case 0:
			{
				string out = "";
				bool flag = false;
				for (int i = 3; i < message.size(); i++)
				{
					if (message[i] == 'p')
					{
						flag = true;
						break;
					}
					out += message[i];
				}
				int portClient = atoi(out.c_str());
				if (flag)
					lastPort = portClient;
				else
				{

					SOCKET _socket;
					_socket = InitSocket();

					bool flag = false;
					for (it = clients.begin(); it != clients.end(); ++it)
						if (portClient == it->first)
						{
							flag = true;
							break;
						}
					if (flag)
						continue;
					sockaddr_in dest_addr;
					dest_addr.sin_family = AF_INET;
					dest_addr.sin_port = htons(portClient);
					HOSTENT *hst;
					// преобразование IP адреса из символьного в сетевой формат
					if (inet_addr(ip.c_str()) != INADDR_NONE)
						dest_addr.sin_addr.s_addr = inet_addr(ip.c_str());
					else
						if (hst = gethostbyname(ip.c_str()))
							((unsigned long *)&dest_addr.sin_addr)[0] =
							((unsigned long **)hst->h_addr_list)[0][0];
						else
							printf("> Invalid address %s:%s\n", ip.c_str(), portClient);

					if (connect(_socket, (sockaddr *)&dest_addr, sizeof(dest_addr)))
						printf("> Connect error %d\n", WSAGetLastError());
					else
					{
						Send(_socket, "/c " + convert(port) + "p");
						Send(_socket, "> Connected " + ip + ":" + convert(port));
						DWORD thID;
						CreateThread(NULL, NULL, GetNewMessage, &_socket, NULL, &thID);
						clients[atoi(out.c_str())] = _socket;
						printf("> Connected new user %s:%s\n", ip.c_str(), out.c_str());
					}
				}
				break;
			}
			case 1:
			{
				pair <string, string> infClient = parser(message);
				clients.erase(atoi(infClient.second.c_str()));
				printf("> %s disconnected\n", infClient.first.c_str());
				break;
			}
			default:
				break;
			}
			if (exitFlag)
				break;
		}
		return 0;
	}

	/// <summary>
	/// обсуживает очередного подключившегося клиента независимо от остальных
	/// </summary>
	/// <param name="client_socket"></param>
	/// <returns></returns>
	static DWORD WINAPI WorkWithClient(LPVOID client_socket)
	{
		while (1)
		{
			string cmd;
			getline(cin, cmd);
			map <int, SOCKET>::iterator it;
			switch (systemCommand(cmd))
			{
			case 0:
			{
				SOCKET _socket;
				_socket = InitSocket();
				pair<string, string> ipPort = parser(cmd);

				bool flag = false;
				for (it = clients.begin(); it != clients.end(); ++it)
					if (ipPort.first == ip && atoi(ipPort.second.c_str()) == it->first)
					{
						LogMessage(usedAdress);
						flag = true;
						break;
					}
				if (flag)
					break;
				sockaddr_in dest_addr;
				dest_addr.sin_family = AF_INET;
				dest_addr.sin_port = htons(atoi(ipPort.second.c_str()));
				HOSTENT *hst;
				// преобразование IP адреса из символьного в сетевой формат
				if (inet_addr(ipPort.first.c_str()) != INADDR_NONE)
					dest_addr.sin_addr.s_addr = inet_addr(ipPort.first.c_str());
				else
					if (hst = gethostbyname(ipPort.first.c_str()))
						((unsigned long *)&dest_addr.sin_addr)[0] =
						((unsigned long **)hst->h_addr_list)[0][0];
					else
						printf("> Invalid address %s:%s\n", ipPort.first, ipPort.second);

				if (connect(_socket, (sockaddr *)&dest_addr, sizeof(dest_addr)))
					printf("> Connect error %d\n", WSAGetLastError());
				else
				{
					Send(_socket, "/c " + convert(port) + "p");
					cout << "> Connect with " << ipPort.first << ":" << ipPort.second << " success\n";
					DWORD thID;
					CreateThread(NULL, NULL, GetNewMessage, &_socket, NULL, &thID);
					clients[atoi(ipPort.second.c_str())] = _socket;
					for (it = clients.begin(); it != clients.end(); ++it)
						Send(it->second, "> Connected new user " + ipPort.first + ":" + convert(port));
				}
				break;
			}
			case 1:
			{
				printf("Exit...\n");
				exitFlag = true;
				for (it = clients.begin(); it != clients.end(); ++it)
					Send(it->second, "/e " + name + ":" + convert(port));
				for (it = clients.begin(); it != clients.end(); ++it)
					Exit(it->second);
				break;
			}
			default:
			{
				for (it = clients.begin(); it != clients.end(); ++it)
					Send(it->second, name + ":" + cmd);
				break;
			}
			}
			if (exitFlag)
				break;
		}
		return 0;
	}
};

