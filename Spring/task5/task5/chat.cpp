#include "stdafx.h"
#include "chat.h"

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

void chat::start()
{
	if (!init())
		exit(0);
	user::exitFlag = false;
	logMessage(welcome);
	logMessage(choosePort);
	scanf("%d", &user::port);
	if (user::port == 0)
	{
		logMessage(errors::incorrectAdress);
		return;
	}
	// создание сокета
	socketEx = user::initSocket();
	// связывание сокета с локальным адресом
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(user::port);
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

	user::clients[user::port] = socketEx;
	sockaddr_in clinetAddres;
	int client_addr_size = sizeof(clinetAddres);
	SOCKET clientSockets[20];
	int pos = 0; 
	
	while ((clientSockets[pos] = accept(socketEx, (sockaddr *)&clinetAddres, &client_addr_size)) && !user::exitFlag)
	{
		DWORD thID;
		CreateThread(NULL, NULL, user::getMessage, &clientSockets[pos], NULL, &thID);
		user::sendMessage(clientSockets[pos], "/c " + convert(user::port) + "p");
		Sleep(50);
		for (it = user::clients.begin(); it != user::clients.end(); ++it)
			user::sendMessage(it->second, "/c " + convert(user::lastPort));
		user::clients[user::lastPort] = clientSockets[pos];
		pos++;
	}
	closesocket(socketEx);
	WSACleanup();
}
