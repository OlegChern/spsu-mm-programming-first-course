#include "stdafx.h"
#pragma once
class Tank {
public:
	string name;
	string developer;
	int combatMass;
	double cost;
	Tank() {};
	Tank(string _name, string _developer, int _combatMass, float _cost);
	virtual void Print();
	virtual void Shoot();
	virtual void Swim();
};