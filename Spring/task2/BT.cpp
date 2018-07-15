#include "stdafx.h"
#pragma once
#include "AbstractClass.cpp"


class BT : public Tank
{
public:
	BT(string TankName, string TankDeveloper, int TankCombatMass, int TankCost)
	{
		Name = TankName;
		Developer = TankDeveloper;
		CombatMass = TankCombatMass;
		Cost = TankCost;
	}

	void GetInfo()
	{
		PrintInfo();
		cout << "  This machine Based of the wheel-tracked car of the American designer Christie\n";
		cout << "     Speed on wheels: " << 22 << "  kilometre per hour\n";
		cout << "     Speed on tracks: " << 25 << "  kilometre per hour\n";
	}
};