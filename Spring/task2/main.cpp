#include "stdafx.h"
#include "Leopard.cpp"
#include "BT.cpp"

int main()
{
	cout << "Fist Tank:\n";
	Leopard FirstTank("Leopard_2A6", "Germany", 62500, 8.5);
	FirstTank.GetInfo();

	cout << "Second Tank:\n";
	BT SecondTank("BT", "Russia", 11050, 8);
	SecondTank.GetInfo();
	system("pause");
	return 0;
}