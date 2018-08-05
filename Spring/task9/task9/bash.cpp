#include "stdafx.h"
#include "echo.cpp"
#include "pwd.cpp"
#include "cat.cpp"
#include "wc.cpp"
#include "parser.cpp"
#include "localValue.cpp"

class bash
{
public:
	string inputString;

	void start()
	{
		cout << "Bash started\n";
		bool stopBash = 0;
		localValue values;
		while (!stopBash)
		{
			getline(cin, inputString);
			parser t(inputString, &values);
			t.pushInList();
			if (t.len == 0)
			{
				errorCommand();
				continue;
			}
			for (int i = 0; i < t.len; i++)
			{
				if (i != 0)
				{
					if (t.listCommands[i - 1]->value == "error")
					{
						errorCommand();
						break;
					}
					else
					{
						if (i - 2 >= 0)
						{
							if (t.listCommands[i]->value == "")
								t.listCommands[i]->value = t.listCommands[i - 2]->memory;
						}
					}
				}

				t.listCommands[i]->execude();

			}
		}
	}

	void errorCommand()
	{
		cout << "Command not recognized, try again\n";
	}

};