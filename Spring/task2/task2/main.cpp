#include "stdafx.h"
#include "Tank.h"
#include "SwimTank.h"
#include "APC.h"

int main()
{
	cout << "FistTank\n";
	SwimTank tank = SwimTank("Scorpion", "Great Britain", 8000, 8);
	tank.Shoot();
	tank.Swim();
	tank.Print();

	cout << "\nSecondTank\n";
	APC tank2 = APC("BT", "Russia", 11050, 8.5);
	tank2.Shoot();
	tank2.Swim();
	tank2.Print();

	system("pause");

	return 0;
}