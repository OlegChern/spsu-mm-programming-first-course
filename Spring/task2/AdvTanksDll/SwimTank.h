#pragma once
#include "../TankDll/Tank.h"
#ifdef SwimTank_EXPORTS  
#define SwimTank_API __declspec(dllexport)
#else  
#define SwimTank_API __declspec(dllimport)   
#endif 
class SwimTank : public Tank
{
public:

	SwimTank(string _name, string _developer, int _combatMass, float _cost) {
		name = _name;
		developer = _developer;
		combatMass = _combatMass;
		cost = _cost;
	}


	void swim();

	void shoot();

	SwimTank();
	~SwimTank();
};

