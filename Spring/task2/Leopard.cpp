#include "stdafx.h"
#pragma once
#include "AbstractClass.cpp"


class Leopard : public Tank
{
public:
	Leopard(string TankName, string TankDeveloper, int TankCombatMass, int TankCost)
	{
		Name = TankName;
		Developer = TankDeveloper;
		CombatMass = TankCombatMass;
		Cost = TankCost;
	}
	void GetInfo()
	{
		PrintInfo();
		cout << "  Speed: 72  kilometre per hour\n\n";
	}
};