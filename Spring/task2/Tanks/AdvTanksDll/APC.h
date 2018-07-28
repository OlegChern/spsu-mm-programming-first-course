#pragma once
#include "Tank.h"
#ifdef APC_EXPORTS  
#define APC_API __declspec(dllexport)   
#else  
#define APC_API __declspec(dllimport)   
#endif 
class APC : public Tank
{
public:
	void swim();
	void shoot();
	APC(string _name, string _developer, int _combatMass, float _cost) {
		name = _name;
		developer = _developer;
		combatMass = _combatMass;
		cost = _cost;
	}
	APC();
	~APC();
};