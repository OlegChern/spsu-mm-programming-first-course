#include "stdafx.h"
#include "../TankDll/Tank.h"
#include "../AdvTanksDll/SwimTank.h"
#include "../AdvTanksDll/APC.h"
int main()
{
	cout << "FistTank\n";
	SwimTank tank = SwimTank("Scorpion", "Great Britain", 8000, 8);
	tank.print();

	cout << "\nSecondTank\n";
	APC tank2 = APC("BT", "Russia", 11050, 8.5);
	tank2.print();

	system("pause");

	return 0;
}