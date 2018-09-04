#include "errors.h"

#pragma once
class user
{
private:
	static string exitCommand;
	map <int, SOCKET>::iterator it;

	static int systemCommand(string s);

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
	static void logMessage(string message);

public:
	static bool exitFlag;
	static string name;
	static map <int, SOCKET> clients;

	/// <summary>
	/// Корректный выход
	/// </summary>
	static void exitCmd(SOCKET socket);

	static DWORD WINAPI getMessage(LPVOID clientSocket);

	/// <summary>
	/// обсуживает очередного подключившегося клиента независимо от остальных
	/// </summary>
	/// <param name="client_socket"></param>
	/// <returns></returns>
	static DWORD WINAPI workWithClient(LPVOID client_socket);
};

