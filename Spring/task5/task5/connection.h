#pragma once
class connection
{
public:
	static string ip;
	static int port;
	static int lastPort;

	static string recieveClient(SOCKET socket);

	static string recieveClient(LPVOID client_socket);

	/// <summary>
	/// ������� �����
	/// </summary>
	/// <returns></returns>
	static SOCKET initSocket();

	/// <summary>
	/// �������� ���������
	/// </summary>
	/// <param name="socket"></param>
	/// <param name="message"></param>
	static void sendMessage(SOCKET socket, string message);

	static SOCKET tryConnect(string ipClient, int portClient);
};

