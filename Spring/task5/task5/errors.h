#pragma once
class errors
{
public:
	static string incorrectAdress;
	static string usedAdress;

	/// <summary>
	/// ���������� ��������� �� ������
	/// �������������� ���������� Winsock 
	/// </summary>
	static void ShowError();

	static void ShowError(SOCKET _socket);

	static bool checkAdress(string inputAdress);
};

