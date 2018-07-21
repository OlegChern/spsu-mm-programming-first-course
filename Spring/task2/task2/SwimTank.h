#include "Tank.h"
#pragma once
class SwimTank : public Tank
{
public:

	SwimTank(string _name, string _developer, int _combatMass, float _cost) {
		name = _name;
		developer = _developer;
		combatMass = _combatMass;
		cost = _cost;
	}


	void Swim();

	void Shoot();

	SwimTank();
	~SwimTank();
};

