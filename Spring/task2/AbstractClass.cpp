#include "stdafx.h"
#pragma once

class Tank
{
public:
	string Name;
	string Developer;
	int CombatMass;
	double Cost;

	void PrintInfo()
	{
		cout << "  Name: " << Name << "\n";
		cout << "  Cost: " << Cost << "  million dollars\n";
		cout << "  Developer: " << Developer << "\n";
		cout << "  Combat Mass: " << CombatMass << "\n";
	}
};