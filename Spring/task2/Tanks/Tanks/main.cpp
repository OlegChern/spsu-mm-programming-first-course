#include "stdafx.h"
#include "Tank.h"
#include "SwimTank.h"
#include "APC.h"
int main()
{
	cout << "FistTank\n";
	Tank tank = SwimTank("Scorpion", "Great Britain", 8000, 8);
	tank.print();

	cout << "\nSecondTank\n";
	Tank tank2 = APC("BT", "Russia", 11050, 8.5);
	tank2.print();

	system("pause");

	return 0;
}