#include "stdafx.h"
#include "command.cpp"
#include "localValue.cpp"
#pragma once
class cat : public command
{
private:
	char line[1000];
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
		ifstream F;
		F.open(fileName, ios::in);
		if (F)
		{
			cout << "Information from file " << fileName << " :\n";
			while (F.getline(line, sizeof(line)))
			{
				for (int i = 0; i < strlen(line); i++)
					memory += line[i];
				memory += " ";
				cout << line << endl;
			}
			F.close();
		}
		else
			cout << "Error opening file " << fileName << "\n";
			
	}

	cat(localValue *t, string s)
	{
		values = t;
		value = s;
	}
};