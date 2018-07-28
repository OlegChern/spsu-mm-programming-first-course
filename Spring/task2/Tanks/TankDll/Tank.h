#pragma once
#ifdef Tank_EXPORTS  
#define Tank_API __declspec(dllexport)   
#else  
#define Tank_API __declspec(dllimport)   
#endif 
#include "stdafx.h"

class  Tank {
public:
	string name;
	string developer;
	int combatMass;
	double cost;
	Tank() {};
	Tank(string _name, string _developer, int _combatMass, float _cost);
	virtual void print();
	virtual void shoot();
	virtual void swim();
};
