#include "Tank.h"
#pragma once
class APC : public Tank
{
public:

	void Swim();

	void Shoot();
	APC(string _name, string _developer, int _combatMass, float _cost) {
		name = _name;
		developer = _developer;
		combatMass = _combatMass;
		cost = _cost;
	}
	
	APC();
	~APC();
};

