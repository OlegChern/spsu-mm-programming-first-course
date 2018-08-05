#include "stdafx.h"
#include "Tank.h"

Tank::Tank(string _name, string _developer, int _combatMass, float _cost)
{
	name = _name;
	developer = _developer;
	combatMass = _combatMass;
	cost = _cost;
}

void Tank::print()
{
	printf("name: %s\ndeveloper: %s\ncombat mass (kg): %i\ncost (million dollars): %lf\n", name.c_str(), developer.c_str(), combatMass, cost);
}

void Tank::shoot()
{
}

void Tank::swim()
{
}

