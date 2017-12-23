#include "stdio.h"
#include "stdlib.h"
#include "header.h"

const int maxLengthList = 3;               // Число предела длинны списков (если равно 3, то перехэширование)

void initHashTable(hashTable* hashTable, int size)            // Создание пустой хэш таблицы
{
	hashTable->size = size;
	hashTable->lists = (list*)malloc(sizeof(list) * size);
	for (int i = 0; i < size; i++)
	{
		hashTable->lists[i].length = 0;
		hashTable->lists[i].head = NULL;
	}
}

int hashFunction(const char* string, int size)              // Хэш функция из ключа в значение
{
	unsigned int hash = 0;

	while (*string != 0)
	{
		hash = (hash * 1664525) + (unsigned char)(*string) + 1013904223;
		string++;
	}
	hash %= size;

	return hash;
}

void addKey(const char* string, hashTable** hashTable)         // Добавление значения по ключу
{
	int value = hashFunction(string, (*hashTable)->size);

	addValue(&((((*hashTable)->lists)[value]).head), string);
	(((*hashTable)->lists)[value]).length++;
	if ((*hashTable)->lists[value].length == maxLengthList)         // Проверка длины списка на предельное значение
	{
		*hashTable = rehash(*hashTable);                     // Присвоение нового указателя на перебалансированную таблицу
	}
}

hashTable* rehash(hashTable* oldHashTable)                           //Перехэширование
{
	hashTable* newHashTable = (hashTable*)malloc(sizeof(hashTable));            
	initHashTable(newHashTable, oldHashTable->size * 2);                     //Создание новой хэш таблицы с диапазоном в 2 раза больше старой
	for (int i = 0; i < oldHashTable->size; i++)
	{
		
		for (int j = 0; j < oldHashTable->lists[i].length; j++)              //Перенос эломентов таблицы в новую, и их удаление в старой
		{
			const char* string = oldHashTable->lists[i].head->string;
			deleteValue(&(oldHashTable->lists[i].head), string); 
			addKey(string, &newHashTable);
		}
	}
	free(oldHashTable->lists);           //Очистка памяти старой хэш таблицы
	free(oldHashTable);                  //
	return newHashTable;
}

void deleteKey(const char* string, hashTable* hashTable)           // Удаление значения по ключу
{
	int hash = hashFunction(string, hashTable->size);
	deleteValue(&(hashTable->lists[hash].head), string);
}

int searchKey(const char* string, hashTable* hashTable)            // Возвращает 1 если значение по данному ключу имеется, иначе 0
{
	int hash = hashFunction(string, hashTable->size);
	return isBelong(&(hashTable->lists[hash].head), string);
}

void deleteHashTable(hashTable* hashTable)                       // Удаление хэш таблицы
{
	for (int i = 0; i < hashTable->size; i++)
	{
		deleteList(&(hashTable->lists[i].head));
	}
	free(hashTable->lists);
	free(hashTable);
}