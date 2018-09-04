#include "stdafx.h"
#include "chat.h"
#include "connection.h"

SOCKET chat::socketEx = 0;

void chat::logMessage(string message)
{
	cout << message.c_str() << std::endl;
}

string chat::convert(int a)
{
	stringstream out;
	out << a;
	return out.str();
}

bool chat::init()
{
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA *)&buff[0]))
	{
		printf("Error WSAStartup %d\n", WSAGetLastError());
		return false;
	}
	return true;
}

BOOL chat::ConsoleHandler(DWORD dwType)
{
	switch (dwType) {
	case CTRL_CLOSE_EVENT:
	{
		map <int, SOCKET>::iterator it;
		for (it = user::clients.begin(); it != user::clients.end(); ++it)
			connection::sendMessage(it->second, "/e " + user::name + ":" + convert(connection::port));
		user::exitCmd(socketEx);
		return TRUE;
	}
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:

		return TRUE;
	default:
		break;
	}
	return FALSE;
}

void chat::start()
{
	if (!init())
		exit(0);
	BOOL ret = SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	user::exitFlag = false;
	logMessage(welcome);
	logMessage(choosePort);
	scanf("%d", &connection::port);
	if (connection::port == 0)
	{
		logMessage(errors::incorrectAdress);
		return;
	}
	// создание сокета
	socketEx = connection::initSocket();
	// связывание сокета с локальным адресом
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(connection::port);
	local_addr.sin_addr.s_addr = 0;
	if (bind(socketEx, (sockaddr *)&local_addr, sizeof(local_addr)))
	{
		errors::ShowError(socketEx);
		logMessage(errors::usedAdress);
		return;
	}

	// ожидание подключений
	if (listen(socketEx, 20))
		errors::ShowError(socketEx);

	logMessage(hello);
	cin >> user::name;
	Sleep(10);
	DWORD thID;
	CreateThread(NULL, NULL, user::workWithClient, &clinetSocket, NULL, &thID);

	user::clients[connection::port] = socketEx;
	sockaddr_in clinetAddres;
	int client_addr_size = sizeof(clinetAddres);
	SOCKET clientSockets[20];
	int pos = 0; 
	
	while ((clientSockets[pos] = accept(socketEx, (sockaddr *)&clinetAddres, &client_addr_size)) && !user::exitFlag)
	{
		DWORD thID;
		CreateThread(NULL, NULL, user::getMessage, &clientSockets[pos], NULL, &thID);
		connection::sendMessage(clientSockets[pos], "/c " + convert(connection::port) + "p");
		Sleep(30);
		int memoryPort = connection::lastPort;
		for (it = user::clients.begin(); it != user::clients.end(); ++it)
			connection::sendMessage(it->second, "/c " + convert(memoryPort));
		user::clients[connection::lastPort] = clientSockets[pos];
		pos++;
	}
	closesocket(socketEx);
	WSACleanup();
}
