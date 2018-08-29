#include "stdafx.h"


string welcome = "---- Chat started ----\n> You can use:\n> /c <ip>:<port> - to connect\n> /e - to exit\n\n";
string joinClient = "> Please enter <ip>:<port> to join";
string choosePort = "> Enter your port: ";
string hello = "> Hello, new member!\n> Your ip: 127.0.0.1\n> Please enter your name: ";
string usedAdress = "> Connect error: This adress is using now";
string incorrectAdress = "> Connect error: Incorrect address";
string exitCommand = "exit";
string ip = "127.0.0.1";

bool exitFlag = false;
string cmd;
int port;
string name;
SOCKET socketEx;
/// <summary>
/// сокет для клиента
/// </summary>
SOCKET clinetSocket;

map <int, SOCKET> clients;
map <int, SOCKET>::iterator it;
int lastPort;

class Message {
public:
	int size;
	string str;
	Message() {
		size = 0;
		str = "";
	}
	Message(int _size, string _str) {
		size = _size;
		str = _str;
	}
};


string convert(int a)
{
	stringstream out;
	out << a;
	return out.str();
}

int systemCommand(string s)
{
	if (s[0] == '/')
	{
		if (s.size() > 2 && s[1] == 'c' && s[2] == ' ')
		{
			return 0;
		}
		else
			if (s[1] == 'e')
				return 1;
	}
	return -1;
}

/// <summary>
/// печатает сообщения  в консоли
/// </summary>
/// <param name="message"></param>
void LogMessage(string message) {
	cout << message.c_str() << std::endl;
}

/// <summary>
/// Инициализация Библиотеки Сокетов
/// </summary>
/// <returns>true- если все ок</returns>
bool Init() {
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA *)&buff[0]))
	{
		printf("Error WSAStartup %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

/// <summary>
/// показывает сообщение об ошибке
/// Деиницилизация библиотеки Winsock 
/// </summary>
void ShowError() {
	printf("Error socket %d\n", WSAGetLastError());
	WSACleanup();
}

void ShowError(SOCKET _socket) {
	printf("Error bind %d\n", WSAGetLastError());
	// закрываем сокет!
	closesocket(_socket);
	WSACleanup();
}

/// <summary>
/// Создает сокет
/// </summary>
/// <returns></returns>
SOCKET InitSocket() {
	SOCKET _socket;
	if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ShowError();
	return _socket;
}

/// <summary>
/// Отделить ip и port
/// </summary>
/// <returns></returns>
pair<string, string> parser(string s)
{
	pair<string, string> res = { "","" };
	bool flag = false;
	for (int i = 3; i < s.size(); i++)
	{
		if (s[i] == ':')
		{
			if (flag)
				return { "","" };
			flag = true;
			continue;
		}
		if (!flag)
			res.first += s[i];
		else
			res.second += s[i];
	}
	return res;
}

/// <summary>
/// отправка сообщения
/// </summary>
/// <param name="socket"></param>
/// <param name="message"></param>
void Send(SOCKET socket, string message) {
	send(socket, message.c_str(), 512, 0);
}

/// <summary>
/// получение сообщения
/// </summary>
/// <param name="socket"></param>
/// <returns></returns>
Message recieveServer(SOCKET socket) {
	char buff[512] = "";
	int size = recv(socket, buff, sizeof(buff), 0);
	return Message(size, string(buff));
}

string recieveClient(SOCKET socket) {
	char buff[512] = "";
	recv(socket, buff, sizeof(buff), 0);
	return string(buff);
}

string recieveClient(LPVOID client_socket) {
	return recieveClient(((SOCKET *)client_socket)[0]);
}

DWORD WINAPI GetNewMessage(LPVOID clientSocket)
{
	string message = "";
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
/// Корректный выход
/// </summary>
void Exit(SOCKET socket) {
	closesocket(socket);
	WSACleanup();
}

void StartThread(SOCKET &socket) {
	DWORD thID;
	HANDLE recieveThread = CreateThread(NULL, NULL, GetNewMessage, &socket, NULL, &thID);
}

/// <summary>
/// обсуживает очередного подключившегося клиента независимо от остальных
/// </summary>
/// <param name="client_socket"></param>
/// <returns></returns>
DWORD WINAPI WorkWithClient(LPVOID client_socket)
{
	while (1)
	{
		getline(cin, cmd);

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
			Exit(socketEx);
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

void start()
{
	if (!Init())
		exit(0);

	LogMessage(welcome);
	LogMessage(choosePort);
	scanf("%d", &port);

	// создание сокета
	socketEx = InitSocket();
	// связывание сокета с локальным адресом
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(port);
	local_addr.sin_addr.s_addr = 0;
	if (bind(socketEx, (sockaddr *)&local_addr, sizeof(local_addr)))
	{
		ShowError(socketEx);
		LogMessage(usedAdress);
		return;
	}

	// ожидание подключений
	if (listen(socketEx, 20))
		ShowError(socketEx);

	LogMessage(hello);
	cin >> name;
	Sleep(10);
	DWORD thID;
	CreateThread(NULL, NULL, WorkWithClient, &clinetSocket, NULL, &thID);

	clients[port] = socketEx;
	sockaddr_in clinetAddres;
	int client_addr_size = sizeof(clinetAddres);
	SOCKET clientSockets[20];
	int pos = 0;

	while ((clientSockets[pos] = accept(socketEx, (sockaddr *)&clinetAddres, &client_addr_size)) && !exitFlag)
	{
		DWORD thID;
		CreateThread(NULL, NULL, GetNewMessage, &clientSockets[pos], NULL, &thID);
		Send(clientSockets[pos], "/c " + convert(port) + "p");
		Sleep(50);
		for (it = clients.begin(); it != clients.end(); ++it)
			Send(it->second, "/c " + convert(lastPort));
		clients[lastPort] = clientSockets[pos];
		pos++;
	}
}

int main()
{
	start();
	system("pause");
	return 0;
}

