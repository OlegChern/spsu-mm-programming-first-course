#include "stdafx.h"
#include "command.cpp"
#include "LocalValue.cpp"
#pragma once

class wc : public command
{
	char line[1000];
	int countLines = 0, countWords = 0;
	size_t countBytes = 0;
	int pos;
public:
	LocalValue * values;
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
				string tmp = "";
				for (int i = 0; i < strlen(line); i++)
				{
					tmp += line[i];
					if (line[i] == ' ')
						countWords++;
				}
				countLines++;
				countWords++;
				countBytes += tmp.size() * sizeof(std::string::value_type);
			}
			F.close();
			cout << "Words: " << countWords << "\n";
			cout << "Lines: " << countLines << "\n";
			cout << "Bytes: " << countBytes << "\n";
			memory = to_string(countWords) + " " + to_string(countLines) + " " + to_string(countBytes);
		}
		else
			cout << "Error opening file\n";
	}

	wc(LocalValue *t, string s)
	{
		values = t;
		value = s;
	}
};