#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "header.h"

int main()
{
	hashTable* testHashTable = (hashTable*)malloc(sizeof(hashTable));

	initHashTable(testHashTable, 1);

	addKey("собака", &testHashTable);             // Добавление значений по ключам в хэш таблицу
	addKey("птица", &testHashTable);
	addKey("лось", &testHashTable);
	addKey("семен", &testHashTable);
	addKey("собака2", &testHashTable);
	addKey("собака3", &testHashTable);
	addKey("собака4", &testHashTable);

	int k = 0;

	k = searchKey("лось", testHashTable);     // Равно 1, т. к. лось есть

	deleteKey("лось", testHashTable);         // Удаление значения по ключу

	k = searchKey("лось", testHashTable);     // Равно 0, т. к. лося нет

	deleteHashTable(testHashTable);           // Удаление хэш таблицы

	_getch();

	return 0;
}