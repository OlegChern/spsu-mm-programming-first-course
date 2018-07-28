#include "stdafx.h"
#include "command.cpp"
#pragma once
namespace fs = std::experimental::filesystem;


class pwd : public command
{
	string NameCatalog = "";
public:
	void execude() {
		setlocale(LC_ALL, "RUS");
		char* buffer = new char[MAX_PATH];
		GetCurrentDirectoryA(MAX_PATH, buffer);
		CharToOemA(buffer, buffer);
		cout << buffer << "\n";
		WIN32_FIND_DATAW wfd;
		HANDLE const hFind = FindFirstFileW(L"./*", &wfd);
		setlocale(LC_ALL, "");

		if (INVALID_HANDLE_VALUE != hFind)
		{
			int k = 0;
			do
			{
				if (k > 1)
					std::wcout << "  " << &wfd.cFileName[0] << std::endl;
				k++;
			} while (NULL != FindNextFileW(hFind, &wfd));

			FindClose(hFind);
		}
	}
};
