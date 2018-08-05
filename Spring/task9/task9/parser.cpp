#include "stdafx.h"
#include "echo.cpp"
#include "pwd.cpp"
#include "cat.cpp"
#include "wc.cpp"
#include "exitCmd.cpp"
#include "localValue.cpp"
#include "conveyor.cpp"
#include "dollar.cpp"
#include "systemCmd.cpp"

class parser
{
private:
	string inputString;
	string names[7] = { "echo", "exit", "pwd", "cat", "wc", "$", "|" };
public:
	int len = 0;
	localValue *values;
	parser(string s, localValue *t)
	{
		inputString = s;
		values = t;
	};
	
	command *listCommands[100];
	
	void pushInList()
	{
		vector <pair<int, string> > convert = identifyCommands(inputString);

		for (int i = 0; i < (int)convert.size(); i++)
		{
			len++;
			switch (convert[i].first)
			{
				case 0:
				{
					//echo *tmp = new echo(convert[i].second);
					listCommands[i] = new echo(values, convert[i].second);
					break;
				}
				case 1:
				{
					listCommands[i] = new exitCmd();
					break;
				}
				case 2:
				{
					listCommands[i] = new pwd();
					break;
				}
				case 3:
				{
					listCommands[i] = new cat(values, convert[i].second);
					break;
				}
				case 4:
				{
					listCommands[i] = new wc(values, convert[i].second);
					break;
				}
				case 5:
				{
					listCommands[i] = new dollar(values, convert[i].second);
					break;
				}
				case 6:
				{
					listCommands[i] = new conveyor(convert[i].second);
					break;
				}
			default:
				listCommands[i] = new systemCmd(convert[i].second);
				break;
			}
		}
	}

	vector <pair<int, string> > identifyCommands(string s)
	{
		vector <string> splitString = split(s);
		vector <pair<int, string> > res;

		// cлучай когда | перва€ или последн€€
		if (numCommand(splitString[0]) == 6 || numCommand(splitString[(int)splitString.size() - 1]) == 6)
		{
			res.push_back({ 6, "error" });
			return res;
		}

		for (int i = 0; i < (int)splitString.size(); i++)
		{
			res.push_back({ numCommand(splitString[i]) , "" });
			string argument = "";
			bool flag = false;
			if (numCommand(splitString[i]) == -1 || numCommand(splitString[i]) == 6 || numCommand(splitString[i]) == 5)
				argument = splitString[i], flag = true;
			i++;
			while (i < (int)splitString.size() && splitString[i] != "|")
			{
				if (flag)
					argument += ' ';
				argument += splitString[i];
				flag = true;
				i++;
			}
			if (i <= (int)splitString.size())
			{
				res[(int)res.size() - 1].second = argument;
				if (i < (int)splitString.size())
					res.push_back({ 6 , "" });
			}
		}

		return res;
	}

	// разделить строку	
	vector <string> split(string s)
	{
		vector <string> res;
		int pos = 0;
		string tmp = "";
		while (pos != (int)s.size())
		{
			if (s[pos] == ' ')
			{
				if ((int)tmp.size() > 0)
					res.push_back(tmp);
				tmp = "";
			}
			else
				tmp += s[pos];
			pos++;
		}
		if ((int)tmp.size() > 0)
			res.push_back(tmp);
		return res;
	}

	// номер команды
	int numCommand(string s)
	{
		if (s[0] == '$')
			return 5;
		if (s[0] == '|' && (int)s.size() == 1)
			return 6;
		for (int i = 0; i < 5; i++)
			if (names[i] == s)
				return i;
		return -1;
	}

};