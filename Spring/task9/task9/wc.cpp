#include "stdafx.h"
#include "command.cpp"
#include "localValue.cpp"
#pragma once

class wc : public command
{
private:
	int countLines = 0, countWords = 0;
	int countBytes = 0;
public:
	localValue * values;

	void execude() {
		string dollarCmd = values->getValue(value);
		if (dollarCmd != "")
			value = dollarCmd;
		vector <string> listOfFiles;
		if ((int)value.size() > 0)
		{
			listOfFiles.push_back("");
			value += " ";
			for (int i = 0; i < value.size(); i++)
				if (value[i] != ' ')
					listOfFiles[(int)listOfFiles.size() - 1] += value[i];
				else
					listOfFiles.push_back("");
		}
		for (int i = 0; i < (int)listOfFiles.size(); i++)
			if (listOfFiles[i] != "")
				printInfo(listOfFiles[i]);
	}

	void printInfo(string fileName)
	{
		FILE *F;
		char buffer[1000];
		strcpy(buffer, fileName.c_str());
		F = fopen(buffer, "r");

		if (F != NULL)
		{
			cout << "Information about file " << fileName << " :\n";
			while (!feof(F))
			{
				fgets(buffer, 1000, F);
				string tmp = "";
				for (int i = 0; i < sizeof(buffer); i++)
				{
					tmp += buffer[i];
					if (buffer[i] == ' ')
						countWords++;
				}
				countLines++;
				countWords++;
			}
			countBytes = ftell(F);
			fclose(F);
			cout << "Words: " << countWords << "\n";
			cout << "Lines: " << countLines << "\n";
			cout << "Bytes: " << countBytes << "\n";
			memory = to_string(countWords) + " " + to_string(countLines) + " " + to_string(countBytes) + " ";
		}
		else
			cout << "Error opening file " << fileName << "\n";
	}

	wc(localValue *t, string s)
	{
		values = t;
		value = s;
	}
};