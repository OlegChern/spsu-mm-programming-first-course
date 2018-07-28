#include "stdafx.h"
#include "command.cpp"
#include "LocalValue.cpp"
#pragma once
class cat : public command
{
	char line[1000];
public:
	LocalValue * values;
	// файл должен находиться в рабочем каталоге
	void execude() {
		string dollarCmd = values->getValue(value);
		if (dollarCmd != "")
			value = dollarCmd;
		setlocale(LC_ALL, "RUS");
		ifstream F;
		F.open(value, std::ifstream::in);
		if (F.is_open())
		{
			while (F.getline(line, sizeof(line)))
			{
				for (int i = 0; i < strlen(line); i++)
					memory += line[i];
				cout << line << endl;
			}
			F.close();
		}
		else
			cout << "Error opening file\n";
	}

	cat(LocalValue *t, string s)
	{
		values = t;
		value = s;
	}
};