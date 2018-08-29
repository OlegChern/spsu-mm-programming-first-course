#include "stdafx.h"
#include "chat.h"

void chat::LogMessage(string message)
{
	cout << message.c_str() << std::endl;
}

void chat::ShowError(SOCKET _socket)
{
	printf("Error bind %d\n", WSAGetLastError());
	// закрываем сокет!
	closesocket(_socket);
	WSACleanup();
}

string chat::convert(int a)
{
	stringstream out;
	out << a;
	return out.str();
}

bool chat::Init()
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
	if (!Init())
		exit(0);
	user::exitFlag = false;
	LogMessage(welcome);
	LogMessage(choosePort);
	scanf("%d", &user::port);

	// создание сокета
	socketEx = user::InitSocket();
	// связывание сокета с локальным адресом
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(user::port);
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
	cin >> user::name;
	Sleep(10);
	DWORD thID;
	CreateThread(NULL, NULL, user::WorkWithClient, &clinetSocket, NULL, &thID);

	user::clients[user::port] = socketEx;
	sockaddr_in clinetAddres;
	int client_addr_size = sizeof(clinetAddres);
	SOCKET clientSockets[20];
	int pos = 0; 
	
	while ((clientSockets[pos] = accept(socketEx, (sockaddr *)&clinetAddres, &client_addr_size)) && !user::exitFlag)
	{
		DWORD thID;
		CreateThread(NULL, NULL, user::GetNewMessage, &clientSockets[pos], NULL, &thID);
		user::Send(clientSockets[pos], "/c " + convert(user::port) + "p");
		Sleep(50);
		for (it = user::clients.begin(); it != user::clients.end(); ++it)
			user::Send(it->second, "/c " + convert(user::lastPort));
		user::clients[user::lastPort] = clientSockets[pos];
		pos++;
	}
	closesocket(socketEx);
	WSACleanup();
}
