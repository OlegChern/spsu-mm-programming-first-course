#include "stdafx.h"
#include "Tank.h"

int main()
{
	cout << "FistTank\n";
	Tank tank = Tank("Leopard_2A6", "Germany", 62500, 8.5);
	tank.Print();

	cout << "\nSecondTank\n";
	tank = Tank("BT", "Russia", 11050, 8);
	tank.Print();

	system("pause");

	return 0;
}