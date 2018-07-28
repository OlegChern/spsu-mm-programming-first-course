#include "stdafx.h"
#include "Node.h"
#include "HashTable.h"


int main()
{

	srand(time(NULL));
	HashTable<int> table(5);
	for (int i = 0; i < 10; i++)
		table.add(i, rand() % 1000);
	int counter = 3;
	while (counter > 0) {
		cout << table.toStr();
		Sleep(10);
		cout << endl;
		counter--;
	}
	system("pause");
	return 0;
}