#include "user.h"
#pragma once

class chat
{
private:
	string welcome = "---- Chat started ----\n> You can use:\n> /c <ip>:<port> - to connect\n> /e - to exit\n\n";
	string joinClient = "> Please enter <ip>:<port> to join";
	string choosePort = "> Enter your port: ";
	string hello = "> Hello, new member!\n> Your ip: 127.0.0.1\n> Please enter your name: ";
	string usedAdress = "> Connect error: This adress is using now";
	SOCKET socketEx;
	SOCKET clinetSocket;
	map <int, SOCKET>::iterator it;
public:
	/// <summary>
	/// печатает сообщения  в консоли
	/// </summary>
	/// <param name="message"></param>
	void LogMessage(string message);

	void ShowError(SOCKET _socket);

	string convert(int a);

	/// <summary>
	/// Инициализация Библиотеки Сокетов
	/// </summary>
	/// <returns>true- если все ок</returns>
	bool Init(); 

	void start();
};

